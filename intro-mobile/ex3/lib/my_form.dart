import 'package:flutter/material.dart';

class MyForm extends StatefulWidget {
  final Function(String, String) addNote;

  const MyForm({super.key, required this.addNote});

  @override
  State<MyForm> createState() => _MyFormState();
}

class _MyFormState extends State<MyForm> {
  final controller1 = TextEditingController();
  final controller2 = TextEditingController();
  final _formKey = GlobalKey<FormState>();

  @override
  void dispose() {
    controller1.dispose();
    controller2.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Form(
      key: _formKey,
      child: Column(
        children: <Widget>[
          TextFormField(
            controller: controller1,
            decoration: const InputDecoration(
              labelText: 'Titre de la note',
            ),
            validator: (value) {
              if (value == null || value.isEmpty) {
                return 'Veuillez entrer du texte';
              }
              return null;
            },
          ),
          TextFormField(
            controller: controller2,
            decoration: const InputDecoration(
              labelText: 'Entrez votre note ici',
            ),
            minLines: 3,
            maxLines: null,
            validator: (value) {
              if (value == null || value.isEmpty) {
                return 'Veuillez entrer du texte';
              }
              return null;
            },
          ),
          ElevatedButton(
            onPressed: () {
              if (_formKey.currentState!.validate()) {
                widget.addNote(
                  controller1.text,
                  controller2.text,
                );
                // clear the text fields
                controller1.clear();
                controller2.clear();
              }
            },
            child: const Text('Soumettre'),
          ),
        ],
      ),
    );
  }
}