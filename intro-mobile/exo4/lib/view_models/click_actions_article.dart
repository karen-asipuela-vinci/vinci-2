import 'package:flutter/foundation.dart';

import '../models/article.dart';

class ClickActionsArticle extends ChangeNotifier {
  final List<Article> _articles = <Article>[];
  bool _showRead = false;

  List<Article> get articles => _articles;
  bool get showRead => _showRead;

// changer si lu ou non lu
  void toggleShowRead() {
    _showRead = !_showRead;
    notifyListeners();
  }

Article? getArticleById(int id) {
    return _articles.firstWhere((element) => element.id == id);
}

void addArticle(Article article) {
  _articles.add(article);
  notifyListeners();
}

  void deleteArticle(Article article) {
    _articles.remove(article);
    notifyListeners();
  }

  void toggleRead(Article article) {
    article.read = !article.read;
    notifyListeners();
  }
}