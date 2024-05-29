import 'package:exo6/view_models/photo_view_model.dart';
import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:exo6/views/photo_gallery.dart';
import 'package:exo6/views/add_photo_screen.dart';
import 'package:provider/provider.dart';

void main() {
  runApp(const MyApp());
}

//infos des chemins
final GoRouter _router = GoRouter(
  initialLocation: '/',
  routes: [
    GoRoute(
      path: '/',
      builder: (context, state) => const PhotoGallery(),
      routes: [
        GoRoute(
          path: 'add-photo',
          builder: (context, state) => const AddPhotoScreen(),
        ),
      ],
    ),
  ],
);

class MyApp extends StatelessWidget {
  const MyApp({super.key});


  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => PhotoViewModel(),
      child: MaterialApp.router(
        routerConfig: _router,
        title: 'Photos App',
        theme: ThemeData(
          colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
          useMaterial3: true,
        ),
      ),
    );
  }
}