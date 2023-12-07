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
vis_teclado.elf.size \

ELFCHECK += \
vis_teclado.elf.elfcheck \


# All Target
all: vis_teclado.elf secondary-outputs

# Tool invocations
vis_teclado.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../vis_teclado_bsp_0/microblaze_0/lib -mxl-pattern-compare -mcpu=v8.30.a -mno-xl-soft-mul -o"vis_teclado.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

vis_teclado.elf.size: vis_teclado.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size vis_teclado.elf  |tee "vis_teclado.elf.size"
	@echo Finished building: $@
	@echo ' '

vis_teclado.elf.elfcheck: vis_teclado.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck vis_teclado.elf -hw ../../p2_hw_platform/system.xml -pe microblaze_0  |tee "vis_teclado.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) vis_teclado.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
