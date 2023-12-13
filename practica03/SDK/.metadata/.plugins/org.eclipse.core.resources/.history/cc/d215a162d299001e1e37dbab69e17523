################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
peripheral_practica03_prog.elf.size \

ELFCHECK += \
peripheral_practica03_prog.elf.elfcheck \


# All Target
all: peripheral_practica03_prog.elf secondary-outputs

# Tool invocations
peripheral_practica03_prog.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../peripheral_practica03_prog_bsp_0/microblaze_0/lib -mxl-pattern-compare -mcpu=v8.30.a -mno-xl-soft-mul -o"peripheral_practica03_prog.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

peripheral_practica03_prog.elf.size: peripheral_practica03_prog.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size peripheral_practica03_prog.elf  |tee "peripheral_practica03_prog.elf.size"
	@echo Finished building: $@
	@echo ' '

peripheral_practica03_prog.elf.elfcheck: peripheral_practica03_prog.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck peripheral_practica03_prog.elf -hw ../../practica03_hw_platform/system.xml -pe microblaze_0  |tee "peripheral_practica03_prog.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) peripheral_practica03_prog.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
