import org.junit.jupiter.api.Test;

import javax.swing.*;

import static java.util.random.RandomGeneratorFactory.all;
import static org.junit.jupiter.api.Assertions.*;

public class TodoListTest {
    @Test
    void addTask() {
        TodoList todoList = new TodoList();

        assertAll(
            () -> assertTrue(todoList.add("task1")),
            () -> assertTrue(todoList.containsTask("task1"))
        );
    }

    @Test
    void addEmptyTask() {
        TodoList todoList = new TodoList();

        assertAll(
            () -> assertFalse(todoList.add("")),
            () -> assertFalse(todoList.containsTask("")),
            //ne pas oublier les nulls !!!
            () -> assertFalse(todoList.add(null)),
            () -> assertFalse(todoList.containsTask(null))
        );
    }
}
