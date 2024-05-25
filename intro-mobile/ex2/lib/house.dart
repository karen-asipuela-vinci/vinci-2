class House {
  bool isToRent = false;
  bool isAHouse = false;
  int squareFootage = 0;
  int numberOfBedrooms = 0;
  int price = 0;
}
// House to buy
House houseBuy = House()
  ..isToRent = false
  ..isAHouse = true
  ..squareFootage = 2000
  ..numberOfBedrooms = 3
  ..price = 200000;

// appartment to buy
House appBuy = House()
  ..isToRent = false
  ..isAHouse = false
  ..squareFootage = 1500
  ..numberOfBedrooms = 2
  ..price = 150000;

// House to rent
House houseRent = House()
  ..isToRent = true
  ..isAHouse = true
  ..squareFootage = 1800
  ..numberOfBedrooms = 3
  ..price = 2000;

// appartment to rent
House appRent = House()
  ..isToRent = true
  ..isAHouse = false
  ..squareFootage = 1200
  ..numberOfBedrooms = 2
  ..price = 1500;