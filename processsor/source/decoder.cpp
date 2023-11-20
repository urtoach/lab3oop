#include <../include/decoder.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// CodeTable methods
CodeTable::CodeTable() {
    opcode_to_table_[1] = []() { return std::make_unique<MovFunc>(); }
    // arithmetic
    opcode_to_table_[] = []() { return std::make_unique<AddFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<SubFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<IncFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<DecFunc>(); }
    // logic
    opcode_to_table_[] = []() { return std::make_unique<NotFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<AndFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<OrFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<XorFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<CmpFunc>(); }
    // shifts
    opcode_to_table_[] = []() { return std::make_unique<ShlFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<ShrFunc>(); }
    // jumps
    opcode_to_table_[] = []() { return std::make_unique<JmpFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<JeFunc>(); }
    opcode_to_table_[] = []() { return std::make_unique<JneFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<JgFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<JgeFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<JlFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<JleFunc>(); };
    // data definition
    opcode_to_table_[] = []() { return std::make_unique<DbFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<DwFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<DdFunc>(); };
    // misc
    opcode_to_table_[] = []() { return std::make_unique<HltFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<RetFunc>(); };
    opcode_to_table_[] = []() { return std::make_unique<CallFunc>(); };
}

std::unique_ptr<CommandDescriptor> CodeTable::commandCreate(unsigned char opcode){
    auto it = opcode_to_table_.find(opcode);
    if (it == opcode_to_table_.end()) {
        return it->second();
    }
    throw std::runtime_error("invalid opcode");
}

