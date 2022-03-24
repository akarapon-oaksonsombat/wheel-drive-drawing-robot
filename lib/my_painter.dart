import 'package:flutter/material.dart';

class MyPainter extends CustomPainter {
  List<List<Offset>> paths = [];
  // List<Offset> offsets = [];
  @override
  void paint(Canvas canvas, Size size) {
    Paint paint = Paint()
      ..style = PaintingStyle.stroke
      ..strokeWidth = 5;
    Path path = Path();

    // TODO : Replace these section with generated code.
    // print(paths.toString() + " - count " + paths.length.toString());
    if (paths != []) {
      for (var element in paths) {
        path.moveTo(element.first.dx, element.first.dy);
        // debugPrint("p?ath");
        for (var point in element) {
          path.lineTo(point.dx, point.dy);
          // debugPrint("line");
        }
      }
    }
    // path.moveTo(20, -180);
    // path.lineTo(20, -170);
    // path.lineTo(20, -170);
    // path.lineTo(20, -170);
    // TODO : Replace these section with generated code.

    canvas.drawPath(path, paint);
  }

  @override
  bool shouldRepaint(MyPainter delegate) {
    return true;
  }
}
