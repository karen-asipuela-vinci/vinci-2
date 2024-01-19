import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import javax.swing.*;

import static java.util.random.RandomGeneratorFactory.all;
import static org.junit.jupiter.api.Assertions.*;

public class TodoListTest {
    //comme on réutilise à chaque fois la même instance de TodoList, on peut la déclarer en attribut de classe
    //et l'initialiser dans la méthode setUp
    //ainsi, on ne crée pas une nouvelle instance à chaque test
    private TodoList todoList;
    @BeforeEach
    void setUp() {
        todoList = new TodoList();
    }

    @Test
    void addTask() {
        assertAll(
            () -> assertTrue(todoList.add("task1")),
            () -> assertTrue(todoList.containsTask("task1"))
        );
    }

    @Test
    void addEmptyTask() {
        assertAll(
            () -> assertFalse(todoList.add("")),
            () -> assertFalse(todoList.containsTask("")),
            //ne pas oublier les nulls !!!
            () -> assertFalse(todoList.add(null)),
            () -> assertFalse(todoList.containsTask(null))
        );
    }

    @Test
    void addExistingTask() {
        //on rajoûte une tâche
        todoList.add("task1");
        assertAll(
                () -> assertFalse(todoList.add("task1")),
                () -> assertTrue(todoList.containsTask("task1"))
        );
    }

    @Test
    void removeTask() {
        todoList.add("task1");
        assertAll(
                () -> assertTrue(todoList.remove("task1")),
                () -> assertFalse(todoList.containsTask("task1"))
        );
    }
}
