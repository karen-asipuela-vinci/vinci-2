import 'dart:convert';
import 'package:flutter/foundation.dart';
import 'package:http/http.dart';

class Film {
  static const baseUrl = "https://sebstreb.github.io/flutter-fiche-5/ghibli-films";

  final String id;
  final String title;
  final String image;
  final String description;
  final String releaseDate;
  final String director;
  final String runningTime;
  final String rtScore;

  const Film({
    required this.id,
    required this.title,
    required this.image,
    required this.description,
    required this.releaseDate,
    required this.director,
    required this.runningTime,
    required this.rtScore,
  });

  Film.fromJson(Map<String, dynamic> json)
      : this(
    id: json["id"],
    title: json["title"],
    image: json["image"],
    description: json["description"],
    releaseDate: json["release_date"],
    director: json["director"],
    runningTime: json["running_time"],
    rtScore: json["rt_score"],
  );


  @override
  String toString() => 'GhibliMovie{id: $id, title: $title, image: $image, '
  'description: $description, releaseDate: $releaseDate, '
  'director: $director, runningTime: $runningTime, rtScore: $rtScore}';

  //! méthode statique et asynchrone
  // Future car on va attendre la réponse du serveur (async)
  static Future<Film> fetchFilm(int id) async {
    var response = await get(Uri.parse(baseUrl));

    if (response.statusCode != 200) {
      throw Exception("Error ${response.statusCode} fetching movie");
    }

    // jsonDecode() transforme la réponse en Map<String, dynamic>
    // fromJson() transforme ce Map en objet Film
    return Film.fromJson(jsonDecode(response.body));
  }

  static Future<List<Film>> fetchFilms() async {
    var response = await get(Uri.parse(baseUrl));

    if (response.statusCode != 200) {
      throw Exception("Error ${response.statusCode} fetching movies");
    }

    // compute() permet de
    // déléguer le traitement de la réponse à un autre isolate
    // isolates = processus légers qui s'exécutent en parallèle
    return compute((input) {
      return jsonDecode(response.body).map<Film>((jsonObj) => Film.fromJson(jsonObj)).toList();
    }, response.body);
  }

}
