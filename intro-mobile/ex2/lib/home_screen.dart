import 'package:ex2/property.dart';
import 'package:ex2/property_widget.dart';
import 'package:flutter/material.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  // rajout de la liste des propriétés
  var showToBuy = false;
  void _toggleShowToBuy() => setState(() => showToBuy = !showToBuy);

  @override
  Widget build(BuildContext context) {
    // modif pour méthode de tri
    final diplayedProperties = [
      for (final property in properties)
        if (showToBuy && property.isToRent || !showToBuy && !property.isToRent)
          property
    ];

    // on rajoute un bouton pour changer le tri
    return Scaffold(
      appBar: AppBar(
        title: const Text('Exo 2 : liste de propriétés'),
        // rajout du bouton Switch pour changer le tri dans actions
        actions: [
          const Text('Buy'),
          Switch(
            value: showToBuy,
            onChanged: (value) => _toggleShowToBuy(),
          ),
          const Text('Rent'),
        ],
      ),
      body: Container(
        padding: const EdgeInsets.all(8),
        child: Center(
          child: SizedBox(
            width: 512.0,
            child: ListView.builder(
              itemCount: diplayedProperties.length,
              itemBuilder: (context, index) => PropertyWidget(property: diplayedProperties[index]),
            )
          )
        )
      ),
    );
  }
}