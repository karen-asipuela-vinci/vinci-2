import 'package:flutter/material.dart';
import 'package:url_launcher/url_launcher.dart';

import '../models/film.dart';

class FilmRow extends StatelessWidget {
  final Film film;

  const FilmRow({super.key, required this.film});

  @override
  Widget build(BuildContext context) {
    return Card(
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Row(
          children: [
            if (MediaQuery.of(context).size.width > 960)
              Image.network(film.image, width: 200),
            const SizedBox(width: 16),
            Expanded(
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    film.releaseDate,
                    style: const TextStyle(color: Colors.grey),
                  ),
                  const Divider(),
                  Text(
                    film.title,
                    style: const TextStyle(fontWeight: FontWeight.bold),
                  ),
                  const Divider(),
                  Text(
                    "${film.rtScore} %",
                    style: TextStyle(
                      color: int.parse(film.rtScore) > 80
                          ? Colors.green
                          : Colors.red,
                    ),
                  ),
                  if (MediaQuery.of(context).size.width > 480) const Divider(),
                  if (MediaQuery.of(context).size.width > 480)
                    Text("${film.runningTime} minutes"),
                  if (MediaQuery.of(context).size.width > 480) const Divider(),
                  if (MediaQuery.of(context).size.width > 480)
                    Text("Directed by ${film.director}"),
                  if (MediaQuery.of(context).size.width > 480) const Divider(),
                  if (MediaQuery.of(context).size.width > 480)
                    Text(
                      film.description,
                      textAlign: TextAlign.justify,
                      softWrap: true,
                    )
                ],
              ),
            )
          ],
        ),
      ),
    );
  }
}