#define _FLASHEEPROM_H_
#ifdef _FLASHEEPROM_H_
#include "stm32f1xx_hal.h"

#define ADDR_FLASH_PAGE_0     ((uint32_t)0x08000000) /* Base @ of Page 0, 1 Kbytes */
#define ADDR_FLASH_PAGE_1     ((uint32_t)0x08000400) /* Base @ of Page 1, 1 Kbytes */
#define ADDR_FLASH_PAGE_2     ((uint32_t)0x08000800) /* Base @ of Page 2, 1 Kbytes */
#define ADDR_FLASH_PAGE_3     ((uint32_t)0x08000C00) /* Base @ of Page 3, 1 Kbytes */
#define ADDR_FLASH_PAGE_4     ((uint32_t)0x08001000) /* Base @ of Page 4, 1 Kbytes */
#define ADDR_FLASH_PAGE_5     ((uint32_t)0x08001400) /* Base @ of Page 5, 1 Kbytes */
#define ADDR_FLASH_PAGE_6     ((uint32_t)0x08001800) /* Base @ of Page 6, 1 Kbytes */
#define ADDR_FLASH_PAGE_7     ((uint32_t)0x08001C00) /* Base @ of Page 7, 1 Kbytes */
#define ADDR_FLASH_PAGE_8     ((uint32_t)0x08002000) /* Base @ of Page 8, 1 Kbytes */
#define ADDR_FLASH_PAGE_9     ((uint32_t)0x08002400) /* Base @ of Page 9, 1 Kbytes */
#define ADDR_FLASH_PAGE_10    ((uint32_t)0x08002800) /* Base @ of Page 10, 1 Kbytes */
#define ADDR_FLASH_PAGE_11    ((uint32_t)0x08002C00) /* Base @ of Page 11, 1 Kbytes */
#define ADDR_FLASH_PAGE_12    ((uint32_t)0x08003000) /* Base @ of Page 12, 1 Kbytes */
#define ADDR_FLASH_PAGE_13    ((uint32_t)0x08003400) /* Base @ of Page 13, 1 Kbytes */
#define ADDR_FLASH_PAGE_14    ((uint32_t)0x08003800) /* Base @ of Page 14, 1 Kbytes */
#define ADDR_FLASH_PAGE_15    ((uint32_t)0x08003C00) /* Base @ of Page 15, 1 Kbytes */
#define ADDR_FLASH_PAGE_16    ((uint32_t)0x08004000) /* Base @ of Page 16, 1 Kbytes */
#define ADDR_FLASH_PAGE_17    ((uint32_t)0x08004400) /* Base @ of Page 17, 1 Kbytes */
#define ADDR_FLASH_PAGE_18    ((uint32_t)0x08004800) /* Base @ of Page 18, 1 Kbytes */
#define ADDR_FLASH_PAGE_19    ((uint32_t)0x08004C00) /* Base @ of Page 19, 1 Kbytes */
#define ADDR_FLASH_PAGE_20    ((uint32_t)0x08005000) /* Base @ of Page 20, 1 Kbytes */
#define ADDR_FLASH_PAGE_21    ((uint32_t)0x08005400) /* Base @ of Page 21, 1 Kbytes */
#define ADDR_FLASH_PAGE_22    ((uint32_t)0x08005800) /* Base @ of Page 22, 1 Kbytes */
#define ADDR_FLASH_PAGE_23    ((uint32_t)0x08005C00) /* Base @ of Page 23, 1 Kbytes */
#define ADDR_FLASH_PAGE_24    ((uint32_t)0x08006000) /* Base @ of Page 24, 1 Kbytes */
#define ADDR_FLASH_PAGE_25    ((uint32_t)0x08006400) /* Base @ of Page 25, 1 Kbytes */
#define ADDR_FLASH_PAGE_26    ((uint32_t)0x08006800) /* Base @ of Page 26, 1 Kbytes */
#define ADDR_FLASH_PAGE_27    ((uint32_t)0x08006C00) /* Base @ of Page 27, 1 Kbytes */
#define ADDR_FLASH_PAGE_28    ((uint32_t)0x08007000) /* Base @ of Page 28, 1 Kbytes */
#define ADDR_FLASH_PAGE_29    ((uint32_t)0x08007400) /* Base @ of Page 29, 1 Kbytes */
#define ADDR_FLASH_PAGE_30    ((uint32_t)0x08007800) /* Base @ of Page 30, 1 Kbytes */
#define ADDR_FLASH_PAGE_31    ((uint32_t)0x08007C00) /* Base @ of Page 31, 1 Kbytes */
#define ADDR_FLASH_PAGE_32    ((uint32_t)0x08008000) /* Base @ of Page 32, 1 Kbytes */
#define ADDR_FLASH_PAGE_33    ((uint32_t)0x08008400) /* Base @ of Page 33, 1 Kbytes */
#define ADDR_FLASH_PAGE_34    ((uint32_t)0x08008800) /* Base @ of Page 34, 1 Kbytes */
#define ADDR_FLASH_PAGE_35    ((uint32_t)0x08008C00) /* Base @ of Page 35, 1 Kbytes */
#define ADDR_FLASH_PAGE_36    ((uint32_t)0x08009000) /* Base @ of Page 36, 1 Kbytes */
#define ADDR_FLASH_PAGE_37    ((uint32_t)0x08009400) /* Base @ of Page 37, 1 Kbytes */
#define ADDR_FLASH_PAGE_38    ((uint32_t)0x08009800) /* Base @ of Page 38, 1 Kbytes */
#define ADDR_FLASH_PAGE_39    ((uint32_t)0x08009C00) /* Base @ of Page 39, 1 Kbytes */
#define ADDR_FLASH_PAGE_40    ((uint32_t)0x0800A000) /* Base @ of Page 40, 1 Kbytes */
#define ADDR_FLASH_PAGE_41    ((uint32_t)0x0800A400) /* Base @ of Page 41, 1 Kbytes */
#define ADDR_FLASH_PAGE_42    ((uint32_t)0x0800A800) /* Base @ of Page 42, 1 Kbytes */
#define ADDR_FLASH_PAGE_43    ((uint32_t)0x0800AC00) /* Base @ of Page 43, 1 Kbytes */
#define ADDR_FLASH_PAGE_44    ((uint32_t)0x0800B000) /* Base @ of Page 44, 1 Kbytes */
#define ADDR_FLASH_PAGE_45    ((uint32_t)0x0800B400) /* Base @ of Page 45, 1 Kbytes */
#define ADDR_FLASH_PAGE_46    ((uint32_t)0x0800B800) /* Base @ of Page 46, 1 Kbytes */
#define ADDR_FLASH_PAGE_47    ((uint32_t)0x0800BC00) /* Base @ of Page 47, 1 Kbytes */
#define ADDR_FLASH_PAGE_48    ((uint32_t)0x0800C000) /* Base @ of Page 48, 1 Kbytes */
#define ADDR_FLASH_PAGE_49    ((uint32_t)0x0800C400) /* Base @ of Page 49, 1 Kbytes */
#define ADDR_FLASH_PAGE_50    ((uint32_t)0x0800C800) /* Base @ of Page 50, 1 Kbytes */
#define ADDR_FLASH_PAGE_51    ((uint32_t)0x0800CC00) /* Base @ of Page 51, 1 Kbytes */
#define ADDR_FLASH_PAGE_52    ((uint32_t)0x0800D000) /* Base @ of Page 52, 1 Kbytes */
#define ADDR_FLASH_PAGE_53    ((uint32_t)0x0800D400) /* Base @ of Page 53, 1 Kbytes */
#define ADDR_FLASH_PAGE_54    ((uint32_t)0x0800D800) /* Base @ of Page 54, 1 Kbytes */
#define ADDR_FLASH_PAGE_55    ((uint32_t)0x0800DC00) /* Base @ of Page 55, 1 Kbytes */
#define ADDR_FLASH_PAGE_56    ((uint32_t)0x0800E000) /* Base @ of Page 56, 1 Kbytes */
#define ADDR_FLASH_PAGE_57    ((uint32_t)0x0800E400) /* Base @ of Page 57, 1 Kbytes */
#define ADDR_FLASH_PAGE_58    ((uint32_t)0x0800E800) /* Base @ of Page 58, 1 Kbytes */
#define ADDR_FLASH_PAGE_59    ((uint32_t)0x0800EC00) /* Base @ of Page 59, 1 Kbytes */
#define ADDR_FLASH_PAGE_60    ((uint32_t)0x0800F000) /* Base @ of Page 60, 1 Kbytes */
#define ADDR_FLASH_PAGE_61    ((uint32_t)0x0800F400) /* Base @ of Page 61, 1 Kbytes */
#define ADDR_FLASH_PAGE_62    ((uint32_t)0x0800F800) /* Base @ of Page 62, 1 Kbytes */
#define ADDR_FLASH_PAGE_63    ((uint32_t)0x0800FC00) /* Base @ of Page 63, 1 Kbytes */
#define ADDR_FLASH_PAGE_64    ((uint32_t)0x08010000) /* Base @ of Page 64, 1 Kbytes */
#define ADDR_FLASH_PAGE_65    ((uint32_t)0x08010400) /* Base @ of Page 65, 1 Kbytes */
#define ADDR_FLASH_PAGE_66    ((uint32_t)0x08010800) /* Base @ of Page 66, 1 Kbytes */
#define ADDR_FLASH_PAGE_67    ((uint32_t)0x08010C00) /* Base @ of Page 67, 1 Kbytes */
#define ADDR_FLASH_PAGE_68    ((uint32_t)0x08011000) /* Base @ of Page 68, 1 Kbytes */
#define ADDR_FLASH_PAGE_69    ((uint32_t)0x08011400) /* Base @ of Page 69, 1 Kbytes */
#define ADDR_FLASH_PAGE_70    ((uint32_t)0x08011800) /* Base @ of Page 70, 1 Kbytes */
#define ADDR_FLASH_PAGE_71    ((uint32_t)0x08011C00) /* Base @ of Page 71, 1 Kbytes */
#define ADDR_FLASH_PAGE_72    ((uint32_t)0x08012000) /* Base @ of Page 72, 1 Kbytes */
#define ADDR_FLASH_PAGE_73    ((uint32_t)0x08012400) /* Base @ of Page 73, 1 Kbytes */
#define ADDR_FLASH_PAGE_74    ((uint32_t)0x08012800) /* Base @ of Page 74, 1 Kbytes */
#define ADDR_FLASH_PAGE_75    ((uint32_t)0x08012C00) /* Base @ of Page 75, 1 Kbytes */
#define ADDR_FLASH_PAGE_76    ((uint32_t)0x08013000) /* Base @ of Page 76, 1 Kbytes */
#define ADDR_FLASH_PAGE_77    ((uint32_t)0x08013400) /* Base @ of Page 77, 1 Kbytes */
#define ADDR_FLASH_PAGE_78    ((uint32_t)0x08013800) /* Base @ of Page 78, 1 Kbytes */
#define ADDR_FLASH_PAGE_79    ((uint32_t)0x08013C00) /* Base @ of Page 79, 1 Kbytes */
#define ADDR_FLASH_PAGE_80    ((uint32_t)0x08014000) /* Base @ of Page 80, 1 Kbytes */
#define ADDR_FLASH_PAGE_81    ((uint32_t)0x08014400) /* Base @ of Page 81, 1 Kbytes */
#define ADDR_FLASH_PAGE_82    ((uint32_t)0x08014800) /* Base @ of Page 82, 1 Kbytes */
#define ADDR_FLASH_PAGE_83    ((uint32_t)0x08014C00) /* Base @ of Page 83, 1 Kbytes */
#define ADDR_FLASH_PAGE_84    ((uint32_t)0x08015000) /* Base @ of Page 84, 1 Kbytes */
#define ADDR_FLASH_PAGE_85    ((uint32_t)0x08015400) /* Base @ of Page 85, 1 Kbytes */
#define ADDR_FLASH_PAGE_86    ((uint32_t)0x08015800) /* Base @ of Page 86, 1 Kbytes */
#define ADDR_FLASH_PAGE_87    ((uint32_t)0x08015C00) /* Base @ of Page 87, 1 Kbytes */
#define ADDR_FLASH_PAGE_88    ((uint32_t)0x08016000) /* Base @ of Page 88, 1 Kbytes */
#define ADDR_FLASH_PAGE_89    ((uint32_t)0x08016400) /* Base @ of Page 89, 1 Kbytes */
#define ADDR_FLASH_PAGE_90    ((uint32_t)0x08016800) /* Base @ of Page 90, 1 Kbytes */
#define ADDR_FLASH_PAGE_91    ((uint32_t)0x08016C00) /* Base @ of Page 91, 1 Kbytes */
#define ADDR_FLASH_PAGE_92    ((uint32_t)0x08017000) /* Base @ of Page 92, 1 Kbytes */
#define ADDR_FLASH_PAGE_93    ((uint32_t)0x08017400) /* Base @ of Page 93, 1 Kbytes */
#define ADDR_FLASH_PAGE_94    ((uint32_t)0x08017800) /* Base @ of Page 94, 1 Kbytes */
#define ADDR_FLASH_PAGE_95    ((uint32_t)0x08017C00) /* Base @ of Page 95, 1 Kbytes */
#define ADDR_FLASH_PAGE_96    ((uint32_t)0x08018000) /* Base @ of Page 96, 1 Kbytes */
#define ADDR_FLASH_PAGE_97    ((uint32_t)0x08018400) /* Base @ of Page 97, 1 Kbytes */
#define ADDR_FLASH_PAGE_98    ((uint32_t)0x08018800) /* Base @ of Page 98, 1 Kbytes */
#define ADDR_FLASH_PAGE_99    ((uint32_t)0x08018C00) /* Base @ of Page 99, 1 Kbytes */
#define ADDR_FLASH_PAGE_100   ((uint32_t)0x08019000) /* Base @ of Page 100, 1 Kbytes */
#define ADDR_FLASH_PAGE_101   ((uint32_t)0x08019400) /* Base @ of Page 101, 1 Kbytes */
#define ADDR_FLASH_PAGE_102   ((uint32_t)0x08019800) /* Base @ of Page 102, 1 Kbytes */
#define ADDR_FLASH_PAGE_103   ((uint32_t)0x08019C00) /* Base @ of Page 103, 1 Kbytes */
#define ADDR_FLASH_PAGE_104   ((uint32_t)0x0801A000) /* Base @ of Page 104, 1 Kbytes */
#define ADDR_FLASH_PAGE_105   ((uint32_t)0x0801A400) /* Base @ of Page 105, 1 Kbytes */
#define ADDR_FLASH_PAGE_106   ((uint32_t)0x0801A800) /* Base @ of Page 106, 1 Kbytes */
#define ADDR_FLASH_PAGE_107   ((uint32_t)0x0801AC00) /* Base @ of Page 107, 1 Kbytes */
#define ADDR_FLASH_PAGE_108   ((uint32_t)0x0801B000) /* Base @ of Page 108, 1 Kbytes */
#define ADDR_FLASH_PAGE_109   ((uint32_t)0x0801B400) /* Base @ of Page 109, 1 Kbytes */
#define ADDR_FLASH_PAGE_110   ((uint32_t)0x0801B800) /* Base @ of Page 110, 1 Kbytes */
#define ADDR_FLASH_PAGE_111   ((uint32_t)0x0801BC00) /* Base @ of Page 111, 1 Kbytes */
#define ADDR_FLASH_PAGE_112   ((uint32_t)0x0801C000) /* Base @ of Page 112, 1 Kbytes */
#define ADDR_FLASH_PAGE_113   ((uint32_t)0x0801C400) /* Base @ of Page 113, 1 Kbytes */
#define ADDR_FLASH_PAGE_114   ((uint32_t)0x0801C800) /* Base @ of Page 114, 1 Kbytes */
#define ADDR_FLASH_PAGE_115   ((uint32_t)0x0801CC00) /* Base @ of Page 115, 1 Kbytes */
#define ADDR_FLASH_PAGE_116   ((uint32_t)0x0801D000) /* Base @ of Page 116, 1 Kbytes */
#define ADDR_FLASH_PAGE_117   ((uint32_t)0x0801D400) /* Base @ of Page 117, 1 Kbytes */
#define ADDR_FLASH_PAGE_118   ((uint32_t)0x0801D800) /* Base @ of Page 118, 1 Kbytes */
#define ADDR_FLASH_PAGE_119   ((uint32_t)0x0801DC00) /* Base @ of Page 119, 1 Kbytes */
#define ADDR_FLASH_PAGE_120   ((uint32_t)0x0801E000) /* Base @ of Page 120, 1 Kbytes */
#define ADDR_FLASH_PAGE_121   ((uint32_t)0x0801E400) /* Base @ of Page 121, 1 Kbytes */
#define ADDR_FLASH_PAGE_122   ((uint32_t)0x0801E800) /* Base @ of Page 122, 1 Kbytes */
#define ADDR_FLASH_PAGE_123   ((uint32_t)0x0801EC00) /* Base @ of Page 123, 1 Kbytes */
#define ADDR_FLASH_PAGE_124   ((uint32_t)0x0801F000) /* Base @ of Page 124, 1 Kbytes */
#define ADDR_FLASH_PAGE_125   ((uint32_t)0x0801F400) /* Base @ of Page 125, 1 Kbytes */
#define ADDR_FLASH_PAGE_126   ((uint32_t)0x0801F800) /* Base @ of Page 126, 1 Kbytes */
#define ADDR_FLASH_PAGE_127   ((uint32_t)0x0801FC00) /* Base @ of Page 127, 1 Kbytes */
#define ADDR_FLASH_PAGE_128   ((uint32_t)0x08020000) /* Base @ of Page 0, 1 Kbytes */
#define ADDR_FLASH_PAGE_129   ((uint32_t)0x08020400) /* Base @ of Page 1, 1 Kbytes */
#define ADDR_FLASH_PAGE_130   ((uint32_t)0x08020800) /* Base @ of Page 2, 1 Kbytes */
#define ADDR_FLASH_PAGE_131   ((uint32_t)0x08020C00) /* Base @ of Page 3, 1 Kbytes */
#define ADDR_FLASH_PAGE_132   ((uint32_t)0x08021000) /* Base @ of Page 4, 1 Kbytes */
#define ADDR_FLASH_PAGE_133   ((uint32_t)0x08021400) /* Base @ of Page 5, 1 Kbytes */
#define ADDR_FLASH_PAGE_134   ((uint32_t)0x08021800) /* Base @ of Page 6, 1 Kbytes */
#define ADDR_FLASH_PAGE_135   ((uint32_t)0x08021C00) /* Base @ of Page 7, 1 Kbytes */
#define ADDR_FLASH_PAGE_136   ((uint32_t)0x08022000) /* Base @ of Page 8, 1 Kbytes */
#define ADDR_FLASH_PAGE_137   ((uint32_t)0x08022400) /* Base @ of Page 9, 1 Kbytes */
#define ADDR_FLASH_PAGE_138   ((uint32_t)0x08022800) /* Base @ of Page 10, 1 Kbytes */
#define ADDR_FLASH_PAGE_139   ((uint32_t)0x08022C00) /* Base @ of Page 11, 1 Kbytes */
#define ADDR_FLASH_PAGE_140   ((uint32_t)0x08023000) /* Base @ of Page 12, 1 Kbytes */
#define ADDR_FLASH_PAGE_141   ((uint32_t)0x08023400) /* Base @ of Page 13, 1 Kbytes */
#define ADDR_FLASH_PAGE_142   ((uint32_t)0x08023800) /* Base @ of Page 14, 1 Kbytes */
#define ADDR_FLASH_PAGE_143   ((uint32_t)0x08023C00) /* Base @ of Page 15, 1 Kbytes */
#define ADDR_FLASH_PAGE_144   ((uint32_t)0x08024000) /* Base @ of Page 16, 1 Kbytes */
#define ADDR_FLASH_PAGE_145   ((uint32_t)0x08024400) /* Base @ of Page 17, 1 Kbytes */
#define ADDR_FLASH_PAGE_146   ((uint32_t)0x08024800) /* Base @ of Page 18, 1 Kbytes */
#define ADDR_FLASH_PAGE_147   ((uint32_t)0x08024C00) /* Base @ of Page 19, 1 Kbytes */
#define ADDR_FLASH_PAGE_148   ((uint32_t)0x08025000) /* Base @ of Page 20, 1 Kbytes */
#define ADDR_FLASH_PAGE_149   ((uint32_t)0x08025400) /* Base @ of Page 21, 1 Kbytes */
#define ADDR_FLASH_PAGE_150   ((uint32_t)0x08025800) /* Base @ of Page 22, 1 Kbytes */
#define ADDR_FLASH_PAGE_151   ((uint32_t)0x08025C00) /* Base @ of Page 23, 1 Kbytes */
#define ADDR_FLASH_PAGE_152   ((uint32_t)0x08026000) /* Base @ of Page 24, 1 Kbytes */
#define ADDR_FLASH_PAGE_153   ((uint32_t)0x08026400) /* Base @ of Page 25, 1 Kbytes */
#define ADDR_FLASH_PAGE_154   ((uint32_t)0x08026800) /* Base @ of Page 26, 1 Kbytes */
#define ADDR_FLASH_PAGE_155   ((uint32_t)0x08026C00) /* Base @ of Page 27, 1 Kbytes */
#define ADDR_FLASH_PAGE_156   ((uint32_t)0x08027000) /* Base @ of Page 28, 1 Kbytes */
#define ADDR_FLASH_PAGE_157   ((uint32_t)0x08027400) /* Base @ of Page 29, 1 Kbytes */
#define ADDR_FLASH_PAGE_158   ((uint32_t)0x08027800) /* Base @ of Page 30, 1 Kbytes */
#define ADDR_FLASH_PAGE_159   ((uint32_t)0x08027C00) /* Base @ of Page 31, 1 Kbytes */
#define ADDR_FLASH_PAGE_160   ((uint32_t)0x08028000) /* Base @ of Page 32, 1 Kbytes */
#define ADDR_FLASH_PAGE_161   ((uint32_t)0x08028400) /* Base @ of Page 33, 1 Kbytes */
#define ADDR_FLASH_PAGE_162   ((uint32_t)0x08028800) /* Base @ of Page 34, 1 Kbytes */
#define ADDR_FLASH_PAGE_163   ((uint32_t)0x08028C00) /* Base @ of Page 35, 1 Kbytes */
#define ADDR_FLASH_PAGE_164   ((uint32_t)0x08029000) /* Base @ of Page 36, 1 Kbytes */
#define ADDR_FLASH_PAGE_165   ((uint32_t)0x08029400) /* Base @ of Page 37, 1 Kbytes */
#define ADDR_FLASH_PAGE_166   ((uint32_t)0x08029800) /* Base @ of Page 38, 1 Kbytes */
#define ADDR_FLASH_PAGE_167   ((uint32_t)0x08029C00) /* Base @ of Page 39, 1 Kbytes */
#define ADDR_FLASH_PAGE_168   ((uint32_t)0x0802A000) /* Base @ of Page 40, 1 Kbytes */
#define ADDR_FLASH_PAGE_169   ((uint32_t)0x0802A400) /* Base @ of Page 41, 1 Kbytes */
#define ADDR_FLASH_PAGE_170   ((uint32_t)0x0802A800) /* Base @ of Page 42, 1 Kbytes */
#define ADDR_FLASH_PAGE_171   ((uint32_t)0x0802AC00) /* Base @ of Page 43, 1 Kbytes */
#define ADDR_FLASH_PAGE_172   ((uint32_t)0x0802B000) /* Base @ of Page 44, 1 Kbytes */
#define ADDR_FLASH_PAGE_173   ((uint32_t)0x0802B400) /* Base @ of Page 45, 1 Kbytes */
#define ADDR_FLASH_PAGE_174   ((uint32_t)0x0802B800) /* Base @ of Page 46, 1 Kbytes */
#define ADDR_FLASH_PAGE_175   ((uint32_t)0x0802BC00) /* Base @ of Page 47, 1 Kbytes */
#define ADDR_FLASH_PAGE_176   ((uint32_t)0x0802C000) /* Base @ of Page 48, 1 Kbytes */
#define ADDR_FLASH_PAGE_177   ((uint32_t)0x0802C400) /* Base @ of Page 49, 1 Kbytes */
#define ADDR_FLASH_PAGE_178   ((uint32_t)0x0802C800) /* Base @ of Page 50, 1 Kbytes */
#define ADDR_FLASH_PAGE_179   ((uint32_t)0x0802CC00) /* Base @ of Page 51, 1 Kbytes */
#define ADDR_FLASH_PAGE_180   ((uint32_t)0x0802D000) /* Base @ of Page 52, 1 Kbytes */
#define ADDR_FLASH_PAGE_181   ((uint32_t)0x0802D400) /* Base @ of Page 53, 1 Kbytes */
#define ADDR_FLASH_PAGE_182   ((uint32_t)0x0802D800) /* Base @ of Page 54, 1 Kbytes */
#define ADDR_FLASH_PAGE_183   ((uint32_t)0x0802DC00) /* Base @ of Page 55, 1 Kbytes */
#define ADDR_FLASH_PAGE_184   ((uint32_t)0x0802E000) /* Base @ of Page 56, 1 Kbytes */
#define ADDR_FLASH_PAGE_185   ((uint32_t)0x0802E400) /* Base @ of Page 57, 1 Kbytes */
#define ADDR_FLASH_PAGE_186   ((uint32_t)0x0802E800) /* Base @ of Page 58, 1 Kbytes */
#define ADDR_FLASH_PAGE_187   ((uint32_t)0x0802EC00) /* Base @ of Page 59, 1 Kbytes */
#define ADDR_FLASH_PAGE_188   ((uint32_t)0x0802F000) /* Base @ of Page 60, 1 Kbytes */
#define ADDR_FLASH_PAGE_189   ((uint32_t)0x0802F400) /* Base @ of Page 61, 1 Kbytes */
#define ADDR_FLASH_PAGE_190   ((uint32_t)0x0802F800) /* Base @ of Page 62, 1 Kbytes */
#define ADDR_FLASH_PAGE_191   ((uint32_t)0x0802FC00) /* Base @ of Page 63, 1 Kbytes */
#define ADDR_FLASH_PAGE_192   ((uint32_t)0x08030000) /* Base @ of Page 64, 1 Kbytes */
#define ADDR_FLASH_PAGE_193   ((uint32_t)0x08030400) /* Base @ of Page 65, 1 Kbytes */
#define ADDR_FLASH_PAGE_194   ((uint32_t)0x08030800) /* Base @ of Page 66, 1 Kbytes */
#define ADDR_FLASH_PAGE_195   ((uint32_t)0x08030C00) /* Base @ of Page 67, 1 Kbytes */
#define ADDR_FLASH_PAGE_196   ((uint32_t)0x08031000) /* Base @ of Page 68, 1 Kbytes */
#define ADDR_FLASH_PAGE_197   ((uint32_t)0x08031400) /* Base @ of Page 69, 1 Kbytes */
#define ADDR_FLASH_PAGE_198   ((uint32_t)0x08031800) /* Base @ of Page 70, 1 Kbytes */
#define ADDR_FLASH_PAGE_199   ((uint32_t)0x08031C00) /* Base @ of Page 71, 1 Kbytes */
#define ADDR_FLASH_PAGE_200   ((uint32_t)0x08032000) /* Base @ of Page 72, 1 Kbytes */
#define ADDR_FLASH_PAGE_201   ((uint32_t)0x08032400) /* Base @ of Page 73, 1 Kbytes */
#define ADDR_FLASH_PAGE_202   ((uint32_t)0x08032800) /* Base @ of Page 74, 1 Kbytes */
#define ADDR_FLASH_PAGE_203   ((uint32_t)0x08032C00) /* Base @ of Page 75, 1 Kbytes */
#define ADDR_FLASH_PAGE_204   ((uint32_t)0x08033000) /* Base @ of Page 76, 1 Kbytes */
#define ADDR_FLASH_PAGE_205   ((uint32_t)0x08033400) /* Base @ of Page 77, 1 Kbytes */
#define ADDR_FLASH_PAGE_206   ((uint32_t)0x08033800) /* Base @ of Page 78, 1 Kbytes */
#define ADDR_FLASH_PAGE_207   ((uint32_t)0x08033C00) /* Base @ of Page 79, 1 Kbytes */
#define ADDR_FLASH_PAGE_208   ((uint32_t)0x08034000) /* Base @ of Page 80, 1 Kbytes */
#define ADDR_FLASH_PAGE_209   ((uint32_t)0x08034400) /* Base @ of Page 81, 1 Kbytes */
#define ADDR_FLASH_PAGE_210   ((uint32_t)0x08034800) /* Base @ of Page 82, 1 Kbytes */
#define ADDR_FLASH_PAGE_211   ((uint32_t)0x08034C00) /* Base @ of Page 83, 1 Kbytes */
#define ADDR_FLASH_PAGE_212   ((uint32_t)0x08035000) /* Base @ of Page 84, 1 Kbytes */
#define ADDR_FLASH_PAGE_213   ((uint32_t)0x08035400) /* Base @ of Page 85, 1 Kbytes */
#define ADDR_FLASH_PAGE_214   ((uint32_t)0x08035800) /* Base @ of Page 86, 1 Kbytes */
#define ADDR_FLASH_PAGE_215   ((uint32_t)0x08035C00) /* Base @ of Page 87, 1 Kbytes */
#define ADDR_FLASH_PAGE_216   ((uint32_t)0x08036000) /* Base @ of Page 88, 1 Kbytes */
#define ADDR_FLASH_PAGE_217   ((uint32_t)0x08036400) /* Base @ of Page 89, 1 Kbytes */
#define ADDR_FLASH_PAGE_218   ((uint32_t)0x08036800) /* Base @ of Page 90, 1 Kbytes */
#define ADDR_FLASH_PAGE_219   ((uint32_t)0x08036C00) /* Base @ of Page 91, 1 Kbytes */
#define ADDR_FLASH_PAGE_220   ((uint32_t)0x08037000) /* Base @ of Page 92, 1 Kbytes */
#define ADDR_FLASH_PAGE_221   ((uint32_t)0x08037400) /* Base @ of Page 93, 1 Kbytes */
#define ADDR_FLASH_PAGE_222   ((uint32_t)0x08037800) /* Base @ of Page 94, 1 Kbytes */
#define ADDR_FLASH_PAGE_223   ((uint32_t)0x08037C00) /* Base @ of Page 95, 1 Kbytes */
#define ADDR_FLASH_PAGE_224   ((uint32_t)0x08038000) /* Base @ of Page 96, 1 Kbytes */
#define ADDR_FLASH_PAGE_225   ((uint32_t)0x08038400) /* Base @ of Page 97, 1 Kbytes */
#define ADDR_FLASH_PAGE_226   ((uint32_t)0x08038800) /* Base @ of Page 98, 1 Kbytes */
#define ADDR_FLASH_PAGE_227   ((uint32_t)0x08038C00) /* Base @ of Page 99, 1 Kbytes */
#define ADDR_FLASH_PAGE_228   ((uint32_t)0x08039000) /* Base @ of Page 100, 1 Kbytes */
#define ADDR_FLASH_PAGE_229   ((uint32_t)0x08039400) /* Base @ of Page 101, 1 Kbytes */
#define ADDR_FLASH_PAGE_230   ((uint32_t)0x08039800) /* Base @ of Page 102, 1 Kbytes */
#define ADDR_FLASH_PAGE_231   ((uint32_t)0x08039C00) /* Base @ of Page 103, 1 Kbytes */
#define ADDR_FLASH_PAGE_232   ((uint32_t)0x0803A000) /* Base @ of Page 104, 1 Kbytes */
#define ADDR_FLASH_PAGE_233   ((uint32_t)0x0803A400) /* Base @ of Page 105, 1 Kbytes */
#define ADDR_FLASH_PAGE_234   ((uint32_t)0x0803A800) /* Base @ of Page 106, 1 Kbytes */
#define ADDR_FLASH_PAGE_235   ((uint32_t)0x0803AC00) /* Base @ of Page 107, 1 Kbytes */
#define ADDR_FLASH_PAGE_236   ((uint32_t)0x0803B000) /* Base @ of Page 108, 1 Kbytes */
#define ADDR_FLASH_PAGE_237   ((uint32_t)0x0803B400) /* Base @ of Page 109, 1 Kbytes */
#define ADDR_FLASH_PAGE_238   ((uint32_t)0x0803B800) /* Base @ of Page 110, 1 Kbytes */
#define ADDR_FLASH_PAGE_239   ((uint32_t)0x0803BC00) /* Base @ of Page 111, 1 Kbytes */
#define ADDR_FLASH_PAGE_240   ((uint32_t)0x0803C000) /* Base @ of Page 112, 1 Kbytes */
#define ADDR_FLASH_PAGE_241   ((uint32_t)0x0803C400) /* Base @ of Page 113, 1 Kbytes */
#define ADDR_FLASH_PAGE_242   ((uint32_t)0x0803C800) /* Base @ of Page 114, 1 Kbytes */
#define ADDR_FLASH_PAGE_243   ((uint32_t)0x0803CC00) /* Base @ of Page 115, 1 Kbytes */
#define ADDR_FLASH_PAGE_244   ((uint32_t)0x0803D000) /* Base @ of Page 116, 1 Kbytes */
#define ADDR_FLASH_PAGE_245   ((uint32_t)0x0803D400) /* Base @ of Page 117, 1 Kbytes */
#define ADDR_FLASH_PAGE_246   ((uint32_t)0x0803D800) /* Base @ of Page 118, 1 Kbytes */
#define ADDR_FLASH_PAGE_247   ((uint32_t)0x0803DC00) /* Base @ of Page 119, 1 Kbytes */
#define ADDR_FLASH_PAGE_248   ((uint32_t)0x0803E000) /* Base @ of Page 120, 1 Kbytes */
#define ADDR_FLASH_PAGE_249   ((uint32_t)0x0803E400) /* Base @ of Page 121, 1 Kbytes */
#define ADDR_FLASH_PAGE_250   ((uint32_t)0x0803E800) /* Base @ of Page 122, 1 Kbytes */
#define ADDR_FLASH_PAGE_251   ((uint32_t)0x0803EC00) /* Base @ of Page 123, 1 Kbytes */
#define ADDR_FLASH_PAGE_252   ((uint32_t)0x0803F000) /* Base @ of Page 124, 1 Kbytes */
#define ADDR_FLASH_PAGE_253   ((uint32_t)0x0803F400) /* Base @ of Page 125, 1 Kbytes */
#define ADDR_FLASH_PAGE_254   ((uint32_t)0x0803F800) /* Base @ of Page 126, 1 Kbytes */
#define ADDR_FLASH_PAGE_255   ((uint32_t)0x0803FC00) /* Base @ of Page 127, 1 Kbytes */

void STMFLASH_Write(uint16_t Addr,uint16_t *pBuffer,uint16_t NumToWrite);

void STMFLASH_Read(uint16_t Addr,uint16_t *pstr,uint16_t NumberToRead);

#endif
