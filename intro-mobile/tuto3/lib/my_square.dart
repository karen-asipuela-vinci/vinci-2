import 'package:flutter/material.dart';
import 'main.dart';
/*
Ce widget affiche le composant dédié à la visualisation de la couleur
du thème actuelle au sein d’un carré, en prenant cette couleur actuelle
en argument.
 */
class MySquare extends StatelessWidget {
  final String color;

  const MySquare({super.key, required this.color});

  @override
  Widget build(BuildContext context) {
    return Expanded(
      child: Center(
        child: Container(
          width: 100,
          height: 100,
          color: getColorValue(color),
        ),
      ),
    );
  }
}
