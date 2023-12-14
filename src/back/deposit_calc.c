#include "../back/extra_calcs.h"

// Вход: сумма вклада, срок размещения, процентная ставка,
//       налоговая ставка, периодичность выплат,
//       капитализация процентов, список пополнений, список частичных снятий
// Выход: начисленные проценты, сумма налога, сумма на вкладе к концу срока

int deposit_calculation(struct deposit_info *dep, Month *months) {
  int status = 1;  // 1 - всё ОК, 0 - ошибка;
  // налог на доход
  double taxRate = 0;
  if (dep->tax_rate != 0.00) {
    taxRate = dep->tax_rate / 100;
  }
  double monthly_rate =
      dep->percent / 12 / 100;  // Процент начисляемый раз в месяц
  double interest_savings = 0;  // начисленные проценты и ждать своей выплаты
  double deposit = dep->input_summ;
  for (int i = 0; i < dep->temp_of_placement && status; ++i) {
    deposit += months[i].plus_value;
    deposit -= months[i].minus_value;
    // Капитализация или нет
    if (dep->capitalization_of_interest == 0) {
      interest_savings = dep->input_summ * monthly_rate;
      dep->input_summ -= months[i].minus_value;
      dep->input_summ += months[i].plus_value;
    } else {
      interest_savings = deposit * monthly_rate;
    }
    dep->tax_amount +=
        interest_savings * taxRate;  // Подсчет общей суммы налогов
    // Выплаты в зависимости от условий
    if (dep->frequency_of_payments > 1 && i > 0 &&
        dep->capitalization_of_interest) {  // Для сложного процента
      if ((i % dep->frequency_of_payments) == 0) {
        deposit = deposit + interest_savings -
                  (interest_savings * taxRate);  // с вычетом налогов
        dep->accrued_interest +=
            interest_savings;  // начисленные проценты без учета налогов
        interest_savings = 0;
      }
    } else {
      deposit = deposit + interest_savings -
                (interest_savings * taxRate);  // с вычетом налогов
      dep->accrued_interest +=
          interest_savings;  // начисленные проценты без учета налогов
      interest_savings = 0;
    }
    if (deposit < 0 || dep->input_summ < 0) status = 0;  // Депозит ушел в минус
  }
  // сумма на вкладе к концу срока:
  dep->result_summ = deposit + interest_savings;
  return status;
}
