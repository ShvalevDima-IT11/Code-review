"""Задание 3. Игра «Угадайка»."""


def main() -> None:
    """Определяет числа, которые Иван мог загадать, по его ответам."""
    maximum_number = int(input("Введите максимальное число: "))
    if maximum_number < 1:
        print("Максимальное число должно быть натуральным.")
        return

    possible_numbers = set(range(1, maximum_number + 1))

    while len(possible_numbers) > 1:
        question = input(
            "Нужное число есть среди вот этих чисел: "
        ).strip()

        if question.casefold() == "помогите!":
            break

        try:
            mentioned_numbers = {
                int(number) for number in question.split()
            }
        except ValueError:
            print("Введите числа через пробел или слово «Помогите!».")
            continue

        answer = input("Ответ Ивана: ").strip().casefold()
        while answer not in {"да", "нет"}:
            print("Введите ответ «Да» или «Нет».")
            answer = input("Ответ Ивана: ").strip().casefold()

        if answer == "да":
            possible_numbers.intersection_update(mentioned_numbers)
        else:
            possible_numbers.difference_update(mentioned_numbers)

    if possible_numbers:
        print(
            "Иван мог загадать следующие числа:",
            *sorted(possible_numbers),
        )
    else:
        print("Возможных чисел не осталось. Проверьте ответы Ивана.")


if __name__ == "__main__":
    main()
