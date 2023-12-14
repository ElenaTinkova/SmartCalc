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
 * \brief Structure for working with input and output data of deposit
 * \param input_summ deposit amount
 * \param temp_of_placement placement term
 * \param percent interest rate
 * \param tax_rate tax rate
 * \param frequency_of_payments payment frequency
 * \param capitalization_of_interest interest capitalization
 * \param list_of_deposits list of deposits of funds
 * \param list_of_partial_withdrawals list of partial withdrawals
 * \param accrued_interest accrued interest
 * \param result_summ amount on the deposit at the end of the term
 * \param tax_amount tax amount for deduction
 */
typedef struct deposit_info {
  double input_summ;
  int temp_of_placement;
  double percent;
  double tax_rate;
  int frequency_of_payments;
  double capitalization_of_interest;
  double list_of_deposits;
  double list_of_partial_withdrawals;

  double accrued_interest;
  double result_summ;
  double tax_amount;
} deposit_info;

/*!
 * \brief Structure for working with deposits and withdrawals in the deposit settlement
 * \param plus_value deposit amount
 * \param minus_value withdrawal amount
 */
typedef struct Month {
  double plus_value;
  double minus_value;
} Month;

/*!
 * \brief Calculates annuity credit
 * \param data data structure with input data for calculation
 * \return returns a structure containing data on overpayment on the loan, monthly payment, and total payments on the loan
 */
credit_output annuity_calculations(credit_input data);

/*!
 * \brief Calculates deposit
 * \param dep pointer to the deposit_info structure containing information about
 * the deposit 
 * \param months pointer to an array of Month structures representing
 * months 
 * \return returns 1 on successful calculation, 0 in case of error, 3 -
 * impossible operations with zero
 */
int deposit_calculation(struct deposit_info *dep, Month *months);

#endif
