import 'package:ex2/property.dart';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';

class PropertyWidget extends StatelessWidget {
  final Property property;

  // rajout du constructeur
  const PropertyWidget({Key? key, required this.property}) : super(key: key);

  // afficher les informations des propriétés
  // utiliser ListTile
  @override
  Widget build(BuildContext context) {
    //permet de rajouter un format de monnaie
    // ici, espace entre milliers et virgule pour les décimales
    // pour l'utiliser : intl dans pubspec.yaml
    final formatCurrency = NumberFormat.simpleCurrency(locale: 'fr_FR');
    return ListTile(
      title: Text('${property.isToRent ? 'To rent' : 'To buy'} : ${property.isAHouse ? 'house' : 'flat'} of ${property.squareFootage} m2'),
      subtitle: Text('Price: ${formatCurrency.format(property.price)}'),
      trailing: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text('Surface: ${property.squareFootage} m²'),
          Text('Bedrooms: ${property.numberOfBedrooms}')
        ],
      ),
    );
  }
}