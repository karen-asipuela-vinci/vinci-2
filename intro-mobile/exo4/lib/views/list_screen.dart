import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

import '../models/article.dart';

class ListScreen extends StatelessWidget {
  const ListScreen({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var showRead = false; // TODO F07 get state from view model
    var articles = [
      for (var article in defaultArticles)
        if (showRead || !article.read) article
    ]; // TODO F07 get state from view model
    return Scaffold(
      appBar: AppBar(
        title: const Text("Articles"),
        backgroundColor: Theme.of(context).colorScheme.primaryContainer,
        actions: [
          IconButton(
            icon: showRead
                ? const Icon(Icons.check_box)
                : const Icon(Icons.check_box_outline_blank),
            onPressed: () {}, // TODO F07 show/hide read articles
          ),
          IconButton(icon: const Icon(Icons.abc), onPressed: () {}),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {}, // TODO F06 go to form screen
        child: const Icon(Icons.add),
      ),
      body: Padding(
        padding: const EdgeInsets.all(32.0),
        child: articles.isEmpty
            ? const Center(
                child: Text("There are no articles yet. Create one!"),
              )
            : ListView.builder(
                itemCount: articles.length,
                itemBuilder: (context, index) {
                  var article = articles[index];
                  return Column(
                    children: [
                      ListTile(
                        leading: IconButton(
                          icon: article.read
                              ? const Icon(Icons.check_box)
                              : const Icon(Icons.check_box_outline_blank),
                          onPressed: () {}, // TODO F07 mark as read
                        ),
                        title: Text(article.title),
                        subtitle: Text(article.author),
                        onTap: () {},
                        // TODO F06 go to article screen with a path parameter (the article id) and passing the article as an extra argument
                        trailing: IconButton(
                          icon: const Icon(Icons.delete),
                          onPressed: () {}, // TODO F07 delete article
                        ),
                      ),
                      const Divider(),
                    ],
                  );
                },
              ),
      ),
    );
  }
}
