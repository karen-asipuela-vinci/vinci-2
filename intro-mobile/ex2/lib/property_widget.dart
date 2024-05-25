import 'package:ex2/property.dart';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';

class PropertyWidget extends StatelessWidget {
  // afficher les informations des propriétés
  // utiliser ListTile
  @override
  Widget build(BuildContext context) {
    //permet de rajouter un format de monnaie
    // ici, espace entre milliers et virgule pour les décimales
    // pour l'utiliser : intl dans pubspec.yaml
    final formatCurrency = NumberFormat.simpleCurrency(locale: 'fr_FR');
    return ListView(
      children: properties.map((property) {
        return ListTile(
          leading: Icon(property.isAHouse ? Icons.home : Icons.apartment),
          title: Text('${property.isToRent ? 'To rent' : 'To sell'} : ${property.isAHouse ? 'house' : 'apartment'} of ${property.squareFootage} m2'),
          subtitle: Text('Price: ${formatCurrency.format(property.price)}€'),
          trailing: Text('Bedrooms: ${property.numberOfBedrooms}'),
        );
      }).toList(),
    );
  }
}