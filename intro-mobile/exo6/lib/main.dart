import 'package:flutter/material.dart';
import 'package:exo6/view_models/photo_view_model.dart';
import 'package:exo6/views/photo_gallery.dart';
import 'package:provider/provider.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => PhotoViewModel(),
      child: MaterialApp(
        home: Scaffold(
          appBar: AppBar(title: const Text('Photo Gallery')),
          body: PhotoGallery(),
        ),
      ),
    );
  }
}
