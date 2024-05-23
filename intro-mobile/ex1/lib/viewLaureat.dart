import 'package:flutter/material.dart';

class ViewLaureat extends StatelessWidget {
  final Map<String, dynamic> laureate;

  const ViewLaureat(
    this.laureate, {
    Key? key,
  }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      width: 500,
      height: 200,
      padding: const EdgeInsets.all(8), // Add some padding
      decoration: BoxDecoration(
        color: Colors.cyan.shade50, // Set the background color to light blue
        borderRadius: BorderRadius.circular(10), // Add rounded corners
      ),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[
          Text(
            '\"${laureate['motivation']}\"',
            style: Theme.of(context).textTheme.headline6,
          ),
          Container(
            padding: const EdgeInsets.all(8), // Add some padding
            decoration: BoxDecoration(
              color: Colors.cyan.shade300, // Set the background color to light blue
              borderRadius: BorderRadius.circular(10), // Add rounded corners
            ),
            child: Text(
              '${laureate['firstname'] ?? ''} ${laureate['surname'] ?? ''}',
            ),
          ),
        ],
      ),
    );
  }
}