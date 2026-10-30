"""Задание 1. Определение страны по названию города."""


def main() -> None:
    """Считывает страны с городами и определяет страну для трёх городов."""
    country_count = int(input("Кол-во стран: "))
    city_to_country: dict[str, str] = {}

    for country_number in range(1, country_count + 1):
        country_data = input(f"{country_number} страна: ").split()
        if not country_data:
            continue

        country = country_data[0]
        for city in country_data[1:]:
            city_to_country[city] = country

    for city_number in range(1, 4):
        city = input(f"{city_number} город: ").strip()
        country = city_to_country.get(city)

        if country is not None:
            print(f"Город {city} расположен в стране {country}.")
        else:
            print(f"По городу {city} данных нет.")


if __name__ == "__main__":
    main()
