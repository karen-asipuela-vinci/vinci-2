import 'package:ex3/home_screen.dart';
import 'package:flutter/material.dart';

import 'my_note.dart';

final notes = List.generate(
  3,
  (index) => MyNote(
    title: "Titre de la note ${index + 1}",
    content: "Contenu de la note ${index + 1}",
  ),
);

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  //add function
  void addNote(String title, String content) => setState(() => notes.add(MyNote(
    title: title,
    content: content,
  )));

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: HomeScreen(notes: notes, addNote: addNote),
      debugShowCheckedModeBanner: false,
    );
  }
}