import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:provider/provider.dart';
import 'package:tuto4/view_models/click_view_model.dart';
import 'package:tuto4/views/user_screen.dart';
import 'views/second_screen.dart';
import 'views/first_screen.dart';

final GoRouter _router = GoRouter(
  initialLocation: '/',
  routes: [
    GoRoute(
      path: '/',
      builder: (context, state) {
        // We can access the number of clicks from the ClickViewModel
        // via the getter clicks, provider is used to get the ClickViewModel
        final int nbClicks =
            Provider.of<ClickViewModel>(context, listen: false).clicks;
        return FirstScreen(nbClicks: nbClicks);
      },
      routes: [
        GoRoute(
          path: 'secondscreen',
          builder: (context, state) => const SecondScreen(),
        ),
        GoRoute(
            path: 'users/:username',
            // We can access the username from the path parameters
            // pathParameters est un Map<String, String>
            builder: (context, state) =>
                UserScreen(username: state.pathParameters['username'] ?? ''),
        ),
      ],
    ),
  ],
);

void main() {
  runApp(ChangeNotifierProvider<ClickViewModel> (
    create: (context) => ClickViewModel(),
  child: const MyApp(),
  ));
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp.router(
      routerConfig: _router,
      title: 'Flutter Demo',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
    );
  }
}
