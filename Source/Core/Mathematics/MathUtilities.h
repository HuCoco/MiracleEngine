#pragma once


#define UNROLLED_LOOP(iterator, number_of_iterations, operation) \
  {                                                                     \
    const int iterator = 0;                                             \
    { operation; }                                                      \
    if ((number_of_iterations) > 1) {                                   \
      const int iterator = 1;                                           \
      { operation; }                                                    \
      if ((number_of_iterations) > 2) {                                 \
        const int iterator = 2;                                         \
        { operation; }                                                  \
        if ((number_of_iterations) > 3) {                               \
          const int iterator = 3;                                       \
          { operation; }                                                \
          if ((number_of_iterations) > 4) {                             \
            for (int iterator = 4; iterator < (number_of_iterations);   \
                 ++iterator) {                                          \
              operation;                                                \
            }                                                           \
          }                                                             \
        }                                                               \
      }                                                                 \
    }                                                                   \
  }

