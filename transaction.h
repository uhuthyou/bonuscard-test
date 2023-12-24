#ifndef TRANSACTION
#define TRANSACTION

#include <iostream>

class Transaction {
public:
    enum class OperationType {
        Deposit,
        Withdrawal
    };

    std::time_t dateTime;
    OperationType operationType;
    double amount;
    double balanceAfterTransaction;
};
#endif // TRANSACTION

