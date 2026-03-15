## Problem 3 Solution
'''cpp
class BankAccount {
    private:
        string name;
        string accountNumber;
        double balance;

    public:
        BankAccount(string,double);
        BankAccount(string,double);

        string getName();
        String getAccountNumber();
        double getBalance();

        void setName();
        void setAccountNumber();
        void setBalance();

        void deposit(double);
        void withdraw(double);

        void transfer(string, string, double);


}
