import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

class SecondScreen extends StatefulWidget {
  const SecondScreen({super.key});

  @override
  State<SecondScreen> createState() => _FirstScreenState();
}

class _FirstScreenState extends State<SecondScreen> {
  var nbClicks = 0;

  @override
  Widget build(BuildContext context) {
    return PopScope(
      // We don't want to pop to the first screen when the back button is pressed
      canPop: false,
      onPopInvoked: (didPop) {
        if (!didPop) {
          // Here we would come back to the first screen passing data
          context.go("/", extra: nbClicks);
        }
      },
      child: Scaffold(
        appBar: AppBar(
          title: const Text("Second screen"),
          backgroundColor: Theme.of(context).colorScheme.primaryContainer,
          /* if we don't use a child route, we would have to create our own back button
          leading: IconButton(
              icon: const Icon(Icons.arrow_back),
              // Here we would come back to the first screen passing data
              onPressed: () {}),*/
        ),
        body: Center(
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              const Text("Hello from second screen."),
              const SizedBox(height: 16),
              Text("There were $nbClicks clicks."),
              const SizedBox(height: 16),
              ElevatedButton(
                onPressed: () => setState(() => nbClicks++),
                child: const Text("click me"),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
