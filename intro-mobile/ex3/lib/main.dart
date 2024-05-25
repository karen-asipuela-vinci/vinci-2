import 'package:ex3/home_screen.dart';
import 'package:flutter/material.dart';

import 'my_note.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: HomeScreen(notes: notes),
      debugShowCheckedModeBanner: false,
    );
  }
}

// liste de notes générées
final notes = List.generate(
  10,
  (index) => MyNote(
    title: "Titre de la note ${index + 1}",
    content: "Contenu de la note ${index + 1}",
  ),
);