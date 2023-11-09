#include "creditcalc.h"

#include <math.h>

double CreditCalc::AnnCredit(double vklad, double percent, int month_num) {
  return vklad * ((percent / 12 / 100) /
                  (1 - pow(1 + (percent / 12 / 100), -month_num)));
}
std::pair<std::vector<double>, double> CreditCalc::DiffCredit(double body,
                                                              double duration,
                                                              double percent) {
  double per_month = body / duration;
  double sum = 0;
  std::vector<double> payment;
  for (int i = 0; i < duration; i++) {
    double remainder = body - per_month * i;
    sum += per_month + remainder * (percent / 100 / 12);
    payment.push_back(per_month + remainder * (percent / 100 / 12));
  }
  return std::make_pair(payment, sum);
}
