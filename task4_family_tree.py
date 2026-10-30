"""Задание 4. Вычисление высоты генеалогического дерева."""


def get_height(
    person: str,
    parents: dict[str, str],
    heights: dict[str, int],
) -> int:
    """Вычисляет высоту человека в генеалогическом дереве.

    Args:
        person: Имя человека, для которого требуется найти высоту.
        parents: Словарь, в котором ключ — потомок, значение — родитель.
        heights: Словарь уже рассчитанных высот.

    Returns:
        Высоту указанного человека относительно родоначальника.
    """
    if person in heights:
        return heights[person]

    parent = parents[person]
    heights[person] = get_height(parent, parents, heights) + 1
    return heights[person]


def main() -> None:
    """Считывает родственные связи и выводит высоты людей по алфавиту."""
    people_count = int(input("Введите количество человек: "))
    if people_count < 1:
        print("Количество человек должно быть положительным.")
        return

    parents: dict[str, str] = {}
    all_people: set[str] = set()

    for pair_number in range(1, people_count):
        child, parent = input(f"{pair_number} пара: ").split()
        parents[child] = parent
        all_people.add(child)
        all_people.add(parent)

    if people_count == 1:
        print(
            "Невозможно определить имя единственного человека: "
            "оно отсутствует во входных данных."
        )
        return

    roots = all_people.difference(parents)
    heights: dict[str, int] = {root: 0 for root in roots}

    print('"Высота" каждого члена семьи:')
    for person in sorted(all_people):
        print(f"{person} {get_height(person, parents, heights)}")


if __name__ == "__main__":
    main()
