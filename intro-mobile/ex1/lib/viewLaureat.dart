import 'package:flutter/material.dart';

class ViewLaureat extends StatelessWidget {
  final Map<String, dynamic> laureate;

  const ViewLaureat(
    this.laureate, {
    Key? key,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: <Widget>[
        Text(
          '\"${laureate['motivation']}\"',
        ),
        Text(
          '${laureate['firstname'] ?? ''} ${laureate['surname'] ?? ''}',
        ),
      ],
    );
  }
}