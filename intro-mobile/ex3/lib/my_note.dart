import 'package:flutter/material.dart';

class MyNote extends StatelessWidget{
  String title;
  String content;
  MyNote({super.key, required this.title, required this.content});

  @override
  Widget build(BuildContext context) {
    return Expanded(
        child: Center(
          child: Container(
            width: 100,
            height: 100,
            color: Colors.blue,
            child: Column(
              children: [
                Text(title),
                Text(content)
              ],
            ),
          ),
        ),
    );
  }

  @override
  bool operator ==(Object other) =>
      identical(this, other) ||
      super == other &&
          other is MyNote &&
          runtimeType == other.runtimeType &&
          title == other.title;

  @override
  int get hashCode => super.hashCode ^ title.hashCode;
}