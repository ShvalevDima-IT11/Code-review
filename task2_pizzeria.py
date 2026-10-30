"""Задание 2. Учёт заказов пиццерии."""


def main() -> None:
    """Суммирует заказы и выводит покупателей и пиццы по алфавиту."""
    orders: dict[str, dict[str, int]] = {}
    order_count = int(input("Введите кол-во заказов: "))

    for order_number in range(1, order_count + 1):
        order_parts = input(f"{order_number} заказ: ").split()
        if len(order_parts) < 3:
            print("Заказ должен содержать покупателя, название пиццы и количество.")
            continue

        buyer = order_parts[0]
        pizza = " ".join(order_parts[1:-1])

        try:
            quantity = int(order_parts[-1])
        except ValueError:
            print("Количество пицц должно быть целым числом.")
            continue

        if quantity < 0:
            print("Количество пицц не может быть отрицательным.")
            continue

        if buyer not in orders:
            orders[buyer] = {}
        if pizza not in orders[buyer]:
            orders[buyer][pizza] = 0
        orders[buyer][pizza] += quantity

    for buyer in sorted(orders):
        print(f"{buyer}:")
        for pizza in sorted(orders[buyer]):
            print(f"    {pizza}: {orders[buyer][pizza]}")


if __name__ == "__main__":
    main()
