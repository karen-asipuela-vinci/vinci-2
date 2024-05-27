import 'package:exo4/views/list_screen.dart';
import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

final GoRouter _routeur = GoRouter(
  // La route initiale est la racine
  initialLocation: '/',
  // Les routes sont définies ici
  routes: [
    GoRoute(
      path: '/',
      // Le builder est une fonction qui prend en paramètre le contexte et l'état
      builder: (context, state) {
        // On retourne un widget list_screen
        return const ListScreen();
      },
    )
  ]
);

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp.router(
      routerConfig: _routeur,
      title: 'Exo4',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
    );
  }
}

