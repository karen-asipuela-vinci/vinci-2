import 'dart:convert';
import 'package:flutter/foundation.dart';
import 'package:http/http.dart' as http;

class Film {
  static const baseUrl = "https://sebstreb.github.io/flutter-fiche-5/ghibli-films";

  final int id;
  final String title;
  final String director;
  final int duration;
  final String link;

  const Film(this.id, this.title, this.director, this.duration, this.link);

  Film.fromJson(Map<String, dynamic> jsonObj)
      : this(
    jsonObj["id"],
    jsonObj["title"],
    jsonObj["director"],
    jsonObj["duration"],
    jsonObj["link"],
  );

  @override
  String toString() =>
      'Film: $title, directed by $director, $duration min, $link';

  //! méthode statique et asynchrone
  // Future car on va attendre la réponse du serveur (async)
  static Future<Film> fetchFilm(int id) async {
    var response = await http.get(Uri.parse("$baseUrl/$id"));

    if (response.statusCode != 200) {
      throw Exception("Error ${response.statusCode} fetching movie");
    }

    // jsonDecode() transforme la réponse en Map<String, dynamic>
    // fromJson() transforme ce Map en objet Film
    return Film.fromJson(jsonDecode(response.body));
  }

  static Future<List<Film>> fetchFilms() async {
    var response = await http.get(Uri.parse("$baseUrl/"));

    if (response.statusCode != 200) {
      throw Exception("Error ${response.statusCode} fetching movies");
    }

    // compute() permet de
    // déléguer le traitement de la réponse à un autre isolate
    // isolates = processus légers qui s'exécutent en parallèle
    return compute((input) {
      final jsonList = jsonDecode(input);
      return jsonList.map<Film>((jsonObj) => Film.fromJson(jsonObj)).toList();
    }, response.body);
  }

}
