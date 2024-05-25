import 'package:flutter/material.dart';
import 'my_note.dart';

class HomeScreen extends StatelessWidget {
  final List<MyNote> notes;

  const HomeScreen({Key? key, required this.notes}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Notes"),
        backgroundColor: Colors.blueGrey,
      ),
      body: ListView.separated(
        itemCount: notes.length,
        separatorBuilder: (context, index) => const Divider(),
        itemBuilder: (context, index) {
          return ListTile(
            title: Text(
                notes[index].title,
                style: const TextStyle(fontWeight: FontWeight.bold),
            ),
            subtitle: Text(notes[index].content),
            trailing: IconButton(
              icon: const Icon(Icons.delete),
              onPressed: () {
                notes.remove(notes[index]);
                Navigator.of(context).pushReplacement(
                  MaterialPageRoute(
                    builder: (context) => HomeScreen(notes: notes),
                  ),
                );
              },
            ),
          );
        },
      ),
    );
  }
}