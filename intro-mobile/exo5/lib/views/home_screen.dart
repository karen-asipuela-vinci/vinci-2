import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

import '../models/film.dart';
import 'film_row.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  var message = "Loading…";
  final films = <Film>[];

  @override
  void initState() {
    Future.delayed(const Duration(seconds: 3), () async {
      try {
        setState(() => message = "Loading, any second now…");
        final response = await Film.fetchFilms();
        setState(() {
          if (response.isEmpty) message = "No movies found…";
          films.addAll(response);
        });
      } catch (error) {
        setState(() => message = error.toString());
      }
    });
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: const Text("exo 5 - ghibli films"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: films.isEmpty
            ? Text(message)
            : ListView.separated(
              itemCount: films.length,
              itemBuilder: (context, index) => FilmRow(film: films[index]),
              separatorBuilder: (context, index) => const SizedBox(height: 8),
         ),
      ),
    );
  }
}