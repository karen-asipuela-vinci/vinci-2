class Photo {
  final int id;
  final String title;
  final String url;
  final String thumbnailUrl;

  // ! attention à bien initialiser les valeurs par défaut
  // et utiliser une , pour séparer les arguments
  Photo({
    this.id = -1,
    this.title = "no title",
    this.url = "no url",
    this.thumbnailUrl = "no thumbnail",
  });

  factory Photo.fromJson(Map<String, dynamic> json) {
    return Photo(
      id: json['id'] ?? "", // Valeur par défaut si null
      title: json['title'] ?? "", // Valeur par défaut si null
      url: json['url'] ?? "", // Valeur par défaut si null
      thumbnailUrl: json['thumbnailUrl'] ?? "", // Valeur par défaut si null
    );
  }
}