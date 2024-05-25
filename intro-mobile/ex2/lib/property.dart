class Property {
  bool isToRent = false;
  bool isAHouse = false;
  int squareFootage = 0;
  int numberOfBedrooms = 0;
  int price = 0;
}
// creer liste de propriétés
List<Property> properties = [
  Property()
    ..isToRent = false
    ..isAHouse = true
    ..squareFootage = 200
    ..numberOfBedrooms = 3
    ..price = 200000,
  Property()
    ..isToRent = false
    ..isAHouse = false
    ..squareFootage = 150
    ..numberOfBedrooms = 2
    ..price = 150000,
  Property()
    ..isToRent = true
    ..isAHouse = true
    ..squareFootage = 180
    ..numberOfBedrooms = 3
    ..price = 2000,
  Property()
    ..isToRent = true
    ..isAHouse = false
    ..squareFootage = 120
    ..numberOfBedrooms = 2
    ..price = 1500,
];