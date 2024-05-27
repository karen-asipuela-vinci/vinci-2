import 'package:exo4/views/article_screen.dart';
import 'package:exo4/views/form_screen.dart';
import 'package:exo4/views/list_screen.dart';
import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

import 'models/article.dart';

final GoRouter _routeur = GoRouter(
  initialLocation: '/',
  routes: [
    GoRoute(
      path: '/',
      builder: (context, state) {
        return const ListScreen();
      },
    ),
    GoRoute(
        path: '/form',
        builder: (context, state) {
          return const FormScreen();
        }
    ),
    GoRoute(
        path: '/article/:id',
        builder: (context, state) {
          // ! state.extra as Article because we need a Article as parameter
          return ArticleScreen(article: state.extra as Article);
        }
    ),
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
      debugShowCheckedModeBanner: false,
    );
  }
}