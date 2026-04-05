#pragma once

/**
 * @file save_file.hpp
 * @brief Основной заголовочный файл для сериализации системы безопасности
 * 
 * Этот файл объединяет все специализации для сериализации и десериализации
 * всех классов системы безопасности в формате YAML.
 * Порядок включения важен для разрешения зависимостей между классами.
 */

// Включаем все специализации в правильном порядке
#include "save_file_comp.hpp"      // Компоненты (Component, Intruder, Wall)
#include "save_file_module.hpp"    // Модули (Module, Network, X_ray, Optical, Military)
#include "save_file_platform.hpp"  // Платформы (Platform, Static, Mobile)
#include "save_file_env.hpp"       // Окружение (Environment)