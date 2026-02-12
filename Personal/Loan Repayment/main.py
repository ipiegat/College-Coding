from dataclasses import dataclass

@dataclass
class Loan:
    name: str
    balance: float
    apr: float
    min_pay: float

def calculate_min(balance, apr, months):
    r = apr / 12
    return balance * r / (1 - (1 + r) ** (-months))

def simulate_avalanche(loans, extra_payment):

    balances = {l.name: l.balance for l in loans}
    aprs = {l.name: l.apr for l in loans}
    mins = {l.name: l.min_pay for l in loans}

    total_interest = 0.0
    total_paid_all_time = 0.0
    payoff_month = {}
    month = 0

    while True:
        active = [name for name in balances if balances[name] > 0]

        if not active:
            break

        month += 1
        payments = {name: 0.0 for name in balances}

        # 1️⃣ Apply interest
        for name in active:
            monthly_interest = balances[name] * (aprs[name] / 12)
            balances[name] += monthly_interest
            total_interest += monthly_interest

        # 2️⃣ Pay minimums
        for name in active:
            payment = min(mins[name], balances[name])
            balances[name] -= payment
            payments[name] += payment

        # 3️⃣ Apply extra to highest APR loan
        remaining_extra = extra_payment

        while remaining_extra > 0:
            active = [name for name in balances if balances[name] > 0]
            if not active:
                break

            target = max(active, key=lambda n: aprs[n])

            extra = min(remaining_extra, balances[target])
            balances[target] -= extra
            payments[target] += extra
            remaining_extra -= extra

        # Track total paid this month
        total_paid_all_time += sum(payments.values())

        # Record payoff month
        for name in balances:
            if balances[name] <= 0 and name not in payoff_month:
                balances[name] = 0
                payoff_month[name] = month

    starting_principal = sum(l.balance for l in loans)

    print("\nStarting minimum payment: $1,771.10")
    print(f"Extra payment per month: ${extra_payment:,.2f}")
    print(f"Total months to debt-free: {month}")
    print(f"Total interest paid: ${total_interest:,.2f}")

    print("\nPayoff order / month paid off:")
    for name, m in sorted(payoff_month.items(), key=lambda x: x[1]):
        print(f"  {name}: month {m}")

    print("\nReconciliation Check:")
    print("Starting principal:", round(starting_principal, 2))
    print("Total interest:", round(total_interest, 2))
    print("Total paid:", round(total_paid_all_time, 2))
    print("Difference (should be ~0):",
          round(total_paid_all_time - (starting_principal + total_interest), 2))

if __name__ == "__main__":

    # ===========================
    # DEFINE LOANS
    # ===========================

    loans = [
        # Private (144 months)
        Loan("3184", 1807.87, 0.0875, calculate_min(1807.87, 0.0875, 144)),
        Loan("8834", 16350.39, 0.0875, calculate_min(16350.39, 0.0875, 144)),
        Loan("6160", 36601.95, 0.0875, calculate_min(36601.95, 0.0875, 144)),
        Loan("4141", 23861.93, 0.0825, calculate_min(23861.93, 0.0825, 144)),
        Loan("3557", 19532.48, 0.0500, calculate_min(19532.48, 0.0500, 144)),
        Loan("7700", 9222.85, 0.0470, calculate_min(9222.85, 0.0470, 144)),
        Loan("7718", 35413.08, 0.0420, calculate_min(35413.08, 0.0420, 144)),

        # Federal (120 months)
        Loan("U2", 8113.34, 0.0653, calculate_min(8113.34, 0.0653, 120)),
        Loan("U1", 7622.65, 0.0639, calculate_min(7622.65, 0.0639, 120)),
        Loan("U3", 2246.54, 0.0550, calculate_min(2246.54, 0.0550, 120)),
        Loan("S1", 4500.00, 0.0550, calculate_min(4500.00, 0.0550, 120)),
        Loan("U4", 5293.29, 0.0499, calculate_min(5293.29, 0.0499, 120)),
        Loan("S2", 777.00, 0.0499, calculate_min(777.00, 0.0499, 120)),    
    ]

    # ===========================
    # RUN SIMULATION
    # ===========================
    simulate_avalanche(loans, extra_payment=500)

    

