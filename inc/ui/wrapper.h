#ifndef IRREDUCIBLE_POLYNOMIALS_WRAPPER_H
#define IRREDUCIBLE_POLYNOMIALS_WRAPPER_H

#include <QWidget>
#include <QGridLayout>

namespace Ui
{
    class Wrapper;
}

class Wrapper : public QWidget
{
    Q_OBJECT
public:
    explicit Wrapper(QWidget* parent = nullptr, int margins = 0);
    ~Wrapper() noexcept;

    void addElement(QWidget* element);
    void addElementAt(QWidget* element, int row, int col,
                      Qt::Alignment alignment = Qt::AlignTop);

private:
    QGridLayout* grid;
};

#endif //IRREDUCIBLE_POLYNOMIALS_WRAPPER_H
