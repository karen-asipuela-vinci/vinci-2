import 'dart:convert';
import 'dart:developer';
import 'package:flutter/foundation.dart';
import 'package:http/http.dart' as http;

import 'photo.dart';

class PhotoRepository {
  final String _baseUrl = 'https://unreal-api.azurewebsites.net';
  final http.Client _http = http.Client();

  Future<List<Photo>> fetchPhotos() async {
    try {
      final response = await _http.get(Uri.parse('$_baseUrl/photos'));
      if (response.statusCode == 200) {
        return compute(
                (responseBodyReceived) => jsonDecode(responseBodyReceived)
                .map<Photo>((jsonObj) => Photo.fromJson(jsonObj))
                .toList(),
            response.body);
      } else {
        throw Exception('Failed to fetch photos');
      }
    } catch (e) {
      throw Exception(e.toString());
    }
  }

  // ajout méthode add photo
  Future<Photo> addPhoto(Photo photo) async {
    try {
      final response = await _http.post(
        Uri.parse('$_baseUrl/photos'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
        body: jsonEncode(<String, String>{
          'title': photo.title,
          'thumbnailUrl': photo.thumbnailUrl,
        }),
      );
      if (response.statusCode == 201) {
        return Photo.fromJson(jsonDecode(response.body));
      } else {
        throw Exception('Failed to add photo');
      }
    } catch (e) {
      throw Exception(e.toString());
    }
  }
}