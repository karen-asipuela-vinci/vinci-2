import 'package:flutter/material.dart';
import 'package:exo6/models/photo.dart';
import 'package:exo6/models/photo_repository.dart';

class PhotoViewModel extends ChangeNotifier {
  final PhotoRepository _photoRepository = PhotoRepository();
  // on rajoute la gestion des erreurs
  String _errorMessage = '';

  Future<List<Photo>> get photos => fetchPhotos();

  // on rajoute un getter pour check l'erreur
  bool get hasError => _errorMessage.isNotEmpty;
  // et le getter pour récupérer le message d'erreur
  String get errorMessage => _errorMessage;

  Future<List<Photo>> fetchPhotos() async {
    try {
      final List<Photo> fetchedPhotos = await _photoRepository.fetchPhotos();
      //return fetchedPhotos.reversed.toList(); // Trier par ID décroissant
      fetchedPhotos.sort(
            (a, b) => b.id.compareTo(a.id),
      );
      return fetchedPhotos;
    } catch (e) {
      _errorMessage = e.toString();
      rethrow;
    }
  }
}

/*
pour la comparaison, si on avait voulu comparer autre chose :
  fetchedPhotos.sort(
        (a, b) => b.id.compareTo(a.id),
      );
 */