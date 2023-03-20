#include "Undo.h"

void UndoAdd::do_undo() {
    repo.remove(added_car_plate);
}

void UndoRemove::do_undo() {
    repo.store(removed_car);
}

void UndoModify::do_undo() {
    switch (type) {
        case 1:
            modified_car.set_make(old_value); break;
        case 2:
            modified_car.set_model(old_value); break;
        case 3:
            modified_car.set_type(old_value); break;
    }
}
