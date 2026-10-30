"""Задание 5. Проверка знания английских переводов."""

GRADE_THRESHOLDS: dict[int, float] = {
    5: 90.0,
    4: 75.0,
    3: 50.0,
}


def read_words(file_path: str) -> list[str]:
    """Читает слова из текстового файла.

    Args:
        file_path: Путь к текстовому файлу.

    Returns:
        Список слов без пробельных символов по краям строк.

    Raises:
        OSError: Если файл не удалось открыть или прочитать.
    """
    with open(file_path, "r", encoding="utf-8") as words_file:
        return [line.strip() for line in words_file]


def get_grade(percentage: float) -> int:
    """Возвращает оценку по принятой в этой программе шкале.

    Args:
        percentage: Процент правильных ответов от 0 до 100.

    Returns:
        Оценку от 2 до 5.

    Note:
        Пороговые значения являются допущением, так как в задании они не указаны.
    """
    for grade, threshold in sorted(
        GRADE_THRESHOLDS.items(),
        key=lambda item: item[1],
        reverse=True,
    ):
        if percentage >= threshold:
            return grade
    return 2


def main() -> None:
    """Проверяет переводы, подсчитывает результат и выводит оценку."""
    russian_path = input("Файл с русскими словами: ").strip()
    english_path = input("Файл с английскими переводами: ").strip()

    try:
        russian_words = read_words(russian_path)
        english_words = read_words(english_path)
    except OSError as error:
        print(f"Не удалось прочитать файл: {error}")
        return

    if len(russian_words) != len(english_words):
        print("Количество строк в файлах должно совпадать.")
        return
    if not russian_words:
        print("Файлы не содержат слов.")
        return
    if any(not word for word in russian_words + english_words):
        print("В файлах обнаружены пустые строки.")
        return

    correct_answers = 0
    for russian_word, english_word in zip(russian_words, english_words):
        answer = input(f"Переведите слово «{russian_word}»: ").strip()
        if answer.casefold() == english_word.casefold():
            print("Верно")
            correct_answers += 1
        else:
            print("Неверно")

    total_words = len(russian_words)
    percentage = correct_answers / total_words * 100
    grade = get_grade(percentage)

    print(f"Правильных ответов: {correct_answers} из {total_words}")
    print(f"Процент правильных ответов: {percentage:.1f}%")
    print(f"Итоговая оценка: {grade}")
    print(
        "Шкала в программе принята условно: 5 — от 90%, 4 — от 75%, "
        "3 — от 50%, иначе 2. При необходимости замените её на шкалу преподавателя."
    )


if __name__ == "__main__":
    main()
