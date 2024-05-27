import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

import '../models/article.dart';

class ArticleScreen extends StatelessWidget {
  final Article article;

  const ArticleScreen({super.key, required this.article});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Article"),
        backgroundColor: Theme.of(context).colorScheme.primaryContainer,
        leading: IconButton(
          icon: const Icon(Icons.arrow_back),
          onPressed: () {
            context.go("/");
          },
        ),
      ),
      floatingActionButton: FloatingActionButton(
        child: article.read
            ? const Icon(Icons.check_box)
            : const Icon(Icons.check_box_outline_blank),
        onPressed: () {}, // TODO F07 mark as read
      ),
      body: Padding(
        padding: const EdgeInsets.all(32),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              article.title,
              style: const TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
              ),
            ),
            Text(
              article.author,
              style: TextStyle(fontSize: 18, color: Colors.grey[700]),
            ),
            const SizedBox(height: 16),
            Expanded(
              child: SingleChildScrollView(
                child: SizedBox(
                  width: double.infinity,
                  child: Text(article.content, textAlign: TextAlign.justify),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
