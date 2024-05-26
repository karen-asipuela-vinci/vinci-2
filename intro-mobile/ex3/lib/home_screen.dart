import 'package:flutter/material.dart';
import 'my_form.dart';
import 'my_note.dart';

class HomeScreen extends StatefulWidget {
  final List<MyNote> notes;
  final Function(String, String) addNote;

  const HomeScreen({super.key, required this.notes, required this.addNote});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {


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
              itemCount: widget.notes.length,
              separatorBuilder: (context, index) => const Divider(),
              itemBuilder: (context, index) {
                return ListTile(
                  title: Text(
                      widget.notes[index].title,
                      style: const TextStyle(fontWeight: FontWeight.bold),
                  ),
                  subtitle: Text(widget.notes[index].content),
                  trailing: IconButton(
                    icon: const Icon(Icons.delete),
                    onPressed: () {
                      widget.notes.remove(widget.notes[index]);
                      Navigator.of(context).pushReplacement(
                        MaterialPageRoute(
                          builder: (context) => HomeScreen(notes: widget.notes, addNote: widget.addNote),
                        ),
                      );
                    },
                  ),
                );
              },
            ),
          ),
          MyForm(addNote: widget.addNote),
        ],
      ),
    );
  }
}