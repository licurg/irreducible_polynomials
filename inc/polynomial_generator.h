#ifndef IRREDUCIBLE_POLYNOMIALS_POLYNOMIAL_GENERATOR_H
#define IRREDUCIBLE_POLYNOMIALS_POLYNOMIAL_GENERATOR_H

#include <QRunnable>

namespace PolynomialGenerator
{
    class PolynomialCounter;
    class PolynomialTask;
}

class PolynomialTask : public QRunnable
{
public:
    explicit PolynomialTask(uint64_t* counter_buffer = nullptr,
                            const uint64_t modulus = 0,
                            const uint8_t degree = 0,
                            const uint8_t task_index = 0,
                            const uint64_t polynomials_per_task = 0,
                            const uint64_t tail = 0);
    ~PolynomialTask() noexcept;
    void run() override;

private:
    uint64_t* counter_buffer;
    uint64_t modulus;
    uint8_t task_index;
    uint64_t polynomials_per_task;
    uint64_t tail;
    uint8_t degree;
    uint64_t current_polynomial;
    uint64_t start_vector;

    uint64_t formula(uint64_t number);
    uint64_t formula_pow(uint64_t number);
    uint64_t formula_shift(uint64_t number);
    uint64_t multiplicate(uint64_t first, uint64_t second);
    uint64_t modulo(QList<uint64_t> polynomial);
    uint64_t modular_mult(uint64_t first, uint64_t second);
    uint64_t modular_add(uint64_t first, uint64_t second);
    void add_polynomials(QList<uint64_t>& first, QList<uint64_t> second);
    void to_polynomial_form(uint64_t number, QList<uint64_t>& polynomial);
    uint64_t to_numeric_form(QList<uint64_t> polynomial);
};

class PolynomialCounter
{
public:
    explicit PolynomialCounter(const uint64_t modulo = 0,
                               const uint8_t degree = 0,
                               uint64_t* polynomial_count = nullptr);
    ~PolynomialCounter() noexcept;

    void start();

private:
    uint8_t degree;
    uint64_t modulo;
    uint8_t max_thread_count;
    uint64_t possible_polynomials;
    uint64_t* polynomial_count;
};



#endif //IRREDUCIBLE_POLYNOMIALS_POLYNOMIAL_GENERATOR_H
