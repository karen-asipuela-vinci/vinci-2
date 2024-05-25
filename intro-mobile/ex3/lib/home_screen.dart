import 'package:flutter/material.dart';
import 'my_form.dart';
import 'my_note.dart';

class HomeScreen extends StatelessWidget {
  final List<MyNote> notes;
  final Function(String, String) addNote;

  const HomeScreen({super.key, required this.notes, required this.addNote});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Notes"),
        backgroundColor: Colors.blueGrey,
      ),
      body: Column(
        children: [
          Expanded(
            child: ListView.separated(
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
                          builder: (context) => HomeScreen(notes: notes, addNote: addNote),
                        ),
                      );
                    },
                  ),
                );
              },
            ),
          ),
          MyForm(addNote: addNote),
        ],
      ),
    );
  }
}