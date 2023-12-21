/*!
\file
\brief Header file with function descriptions used for working with credit and deposit calculators.
*/

#ifndef EXTRA_CALC_H
#define EXTRA_CALC_H

#include <math.h>

/*!
 * \brief enumeration for determining the type of credit
 * \param annuity 1 - annuity
 * \param differentiated 2 - differentiated
 */
typedef enum { annuity = 1, differentiated = 2 } credit_type;

/*!
 * \brief Structure for working with input data of annuity credit
 * \param amount total loan amount
 * \param term loan term
 * \param percent interest rate
 */
typedef struct credit {
  double amount;
  int term;
  double percent;
} credit_input;

/*!
 * \brief Structure for working with output data of annuity credit
 * \param interest_overpayment overpayment on the loan
 * \param total_payments total payments on the loan
 * \param monthly_payment monthly payment
 */
typedef struct credit_calc {
  double interest_overpayment;
  double total_payments;
  double monthly_payment;
} credit_output;


/*!
 * \brief Calculates annuity credit
 * \param data data structure with input data for calculation
 * \return returns a structure containing data on overpayment on the loan, monthly payment, and total payments on the loan
 */
credit_output annuity_calculations(credit_input data);

#endif
