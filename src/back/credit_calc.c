#include "../back/extra_calcs.h"

credit_output annuity_calculations(credit_input data) {
  credit_output result;
  double monthly_percent = data.percent / 12 / 100;
  result.monthly_payment =
      data.amount * ((monthly_percent * pow((1 + monthly_percent), data.term)) /
                     ((pow((1 + monthly_percent), data.term)) - 1));

  result.interest_overpayment =
      data.term * result.monthly_payment - data.amount;

  result.total_payments = result.interest_overpayment + data.amount;
  return result;
}
