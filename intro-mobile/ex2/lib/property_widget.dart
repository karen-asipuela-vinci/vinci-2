import 'package:ex2/property.dart';
import 'package:flutter/material.dart';

class PropertyWidget extends StatelessWidget {
  // afficher les informations des propriétés
  // utiliser ListTile
  @override
  Widget build(BuildContext context) {
    return ListView(
      children: properties.map((property) {
        return ListTile(
          leading: Icon(property.isAHouse ? Icons.home : Icons.apartment),
          title: Text('${property.isToRent ? 'To rent' : 'To sell'} : ${property.isAHouse ? 'house' : 'apartment'} of ${property.squareFootage} m2'),
          subtitle: Text('Price: ${property.price}'),
          trailing: Text('Bedrooms: ${property.numberOfBedrooms}'),
        );
      }).toList(),
    );
  }
}