#include <QDebug>
#include <QThreadPool>
#include <cmath>

#include "polynomial_generator.h"

PolynomialTask::PolynomialTask(uint64_t* counter_buffer,
                               const uint64_t modulus, const uint8_t degree,
                               const uint8_t task_index,
                               const uint64_t polynomials_per_task,
                               const uint64_t tail) : QRunnable()
{
    this->counter_buffer = counter_buffer;
    this->modulus = modulus;
    this->degree = degree;
    this->task_index = task_index;
    this->polynomials_per_task = polynomials_per_task;
    this->tail = tail;
    this->start_vector =
            static_cast<uint64_t>(std::pow(this->modulus,this->modulus - 1));
}
PolynomialTask::~PolynomialTask() noexcept
{

}

void PolynomialTask::run()
{
#ifdef DEBUG
    qDebug() << "Thread running " << QThread::currentThread()
             << "\nTask index: " << this->task_index
             << "\nPolynomials per task: " << this->polynomials_per_task
             << "\nTail: " << this->tail;
#endif
    *this->counter_buffer = 0;

    this->current_polynomial =
            static_cast<uint64_t>(std::pow(this->modulus, this->degree))
            + (this->task_index * this->polynomials_per_task);

    const uint64_t all_polynomials = this->polynomials_per_task + this->tail;
    const uint64_t max_index = this->degree;
    for (uint64_t index = 0; index < all_polynomials; ++index)
    {
        if (this->current_polynomial % this->modulus == 0) {
            this->current_polynomial++;
            continue;
        }
        uint64_t result = this->start_vector;
        for (int64_t i = 1; i < max_index; ++i)
            if ((result = formula(result)) == 1)
                if (i == (max_index - 1)) (*this->counter_buffer)++;

        this->current_polynomial++;
    }
#ifdef DEBUG
    qDebug() << "Calculation ended " << QThread::currentThread();
#endif
}

uint64_t PolynomialTask::formula(uint64_t number)
{
    return formula_shift(formula_pow(number));
}

uint64_t PolynomialTask::formula_pow(uint64_t number)
{
    uint64_t result = number;
    for (int64_t i = 1; i < this->modulus; ++i) {
        result = multiplicate(result, number);
    }
    return result;
}

uint64_t PolynomialTask::formula_shift(uint64_t number)
{
    return multiplicate(number, this->start_vector);
}

uint64_t PolynomialTask::multiplicate(uint64_t first, uint64_t second)
{
    if (first == 0 || second == 0) return 0;

    QList<uint64_t> result_polynomial;

    QList<uint64_t> first_polynomial;
    to_polynomial_form(first, first_polynomial);

    QList<uint64_t> second_polynomial;
    to_polynomial_form(second, second_polynomial);

    const uint64_t first_size = first_polynomial.count();
    const uint64_t second_size = second_polynomial.count();
    const uint64_t result_size = first_size + second_size - 1;
    for (uint64_t i = 0; i < result_size; ++i)
        result_polynomial.append(0);

    for (int64_t i = 0; i < second_size; ++i)
    {
        for (int64_t j = 0; j < first_size; ++j)
        {
            result_polynomial[i + j] =
                    modular_add(result_polynomial[i + j],
                                modular_mult(first_polynomial[j],
                                             second_polynomial[i]));
        }
    }
    return modulo(result_polynomial);
}

uint64_t PolynomialTask::modulo(QList<uint64_t> polynomial)
{
    const uint64_t maximum =
            static_cast<uint64_t>(std::pow(this->modulus, this->degree)) - 1;

    uint64_t result = to_numeric_form(polynomial);
    if (result <= maximum) return result;

    QList<uint64_t> modulus_polynomial;
    to_polynomial_form(this->current_polynomial, modulus_polynomial);

    while ((result = to_numeric_form(polynomial)) > maximum)
        add_polynomials(polynomial, modulus_polynomial);

    return result;
}

uint64_t PolynomialTask::modular_mult(uint64_t first, uint64_t second)
{
    return (first * second) % this->modulus;
}

uint64_t PolynomialTask::modular_add(uint64_t first, uint64_t second)
{
    return (first + second) % this->modulus;
}

void PolynomialTask::add_polynomials(QList<uint64_t> &first,
                                     QList<uint64_t> second)
{
    const uint64_t first_size = first.count();
    const uint64_t second_size = second.count();
    for (int64_t second_i = second_size - 1; second_i >= 0; --second_i)
    {
        const int64_t first_i = first_size - (second_size - second_i - 1) - 1;
        first[first_i] = modular_add(first[first_i], second[second_i]);
    }
    for (int64_t i = first_size - 1; i >= 0; --i)
    {
        if (first[i] == 0) first.removeLast();
        else break;
    }
}

void PolynomialTask::to_polynomial_form(uint64_t number,
                                        QList<uint64_t> &polynomial)
{
    while (number > 0)
    {
        polynomial.append(number % this->modulus);
        number /= this->modulus;
    }
}

uint64_t PolynomialTask::to_numeric_form(QList<uint64_t> polynomial)
{
    uint64_t result = 0;
    const uint64_t size = polynomial.count();
    for (int64_t i = size - 1; i >= 0; --i)
    {
        result += polynomial.takeAt(i)
                * static_cast<uint64_t>(std::pow(this->modulus, i));
    }
    return result;
}

PolynomialCounter::PolynomialCounter(const uint64_t modulo,
                                     const uint8_t degree,
                                     uint64_t* polynomial_count)
{
    this->modulo = modulo;
    this->possible_polynomials =
            static_cast<uint64_t>(std::pow(modulo, degree));
            //* (this->modulo - 1);
#ifdef DEBUG
    qDebug() << "Possible polynomials: " << this->possible_polynomials;
#endif
    this->polynomial_count = polynomial_count;
    this->degree = degree;
    this->max_thread_count = QThreadPool::globalInstance()->maxThreadCount();
#ifdef DEBUG
    qDebug() << "Max thread count: " << this->max_thread_count;
#endif
}
PolynomialCounter::~PolynomialCounter() noexcept
{

}

void PolynomialCounter::start()
{
    uint64_t count_buffers[this->max_thread_count];
    uint64_t polynomials_per_task =
            this->possible_polynomials / this->max_thread_count;
    uint64_t tail = this->possible_polynomials % this->max_thread_count;

    for (uint8_t task_i = 0; task_i < this->max_thread_count; ++task_i)
    {
        uint64_t current_tail = 0U;

        if (task_i == (this->max_thread_count - 1)) current_tail = tail;
        PolynomialTask* polynomial_task = new PolynomialTask(
                &count_buffers[task_i], this->modulo, this->degree,
                task_i, polynomials_per_task, current_tail);
        QThreadPool::globalInstance()->start(polynomial_task);
    }
#ifdef DEBUG
    qDebug() << "Waiting for count work";
#endif
    QThreadPool::globalInstance()->waitForDone();
    *this->polynomial_count =
            std::accumulate(count_buffers,
                            count_buffers + this->max_thread_count, 0);
#ifdef DEBUG
    qDebug() << "Polynomials counted: " << *this->polynomial_count;
#endif
}