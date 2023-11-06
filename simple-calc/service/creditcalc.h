#ifndef CREDITCALC_H
#define CREDITCALC_H
#include <vector>
#include <QStringList>
class CreditCalc
{
    CreditCalc()=delete;
public:
    static double AnnCredit(double vklad, double percent, int month_num);
    static std::pair<QStringList,double> DiffCredit(double body, double duration,
                             double percent);
};


#endif // CREDITCALC_H
